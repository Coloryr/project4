/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <dmac.h>
#include <fpioa.h>
#include <kendryte-standalone-sdk/lib/drivers/include/spi.h>
#include <stdio.h>
#include <string.h>
#include <sysctl.h>
#include "DataSave/w25qxx.h"

spi_device_num_t spi_bus_no = SPI_DEVICE_0;
spi_chip_select_t spi_chip_select = SPI_CHIP_SELECT_0;

static w25qxx_status_t w25qxx_receive_data(uint8_t *cmd_buff, uint8_t cmd_len, uint8_t *rx_buff, uint32_t rx_len)
{
    spi_receive_data_standard(spi_bus_no, spi_chip_select, cmd_buff, cmd_len, rx_buff, rx_len);
    return W25QXX_OK;
}

static w25qxx_status_t w25qxx_send_data(uint8_t *cmd_buff, uint8_t cmd_len, uint8_t *tx_buff, uint32_t tx_len)
{
    spi_send_data_standard(spi_bus_no, spi_chip_select, cmd_buff, cmd_len, tx_buff, tx_len);
    return W25QXX_OK;
}

w25qxx_status_t w25qxx_read_id(uint8_t *manuf_id, uint8_t *device_id)
{
    uint8_t cmd[4] = {READ_ID, 0x00, 0x00, 0x00};
    uint8_t data[2] = {0};

    w25qxx_receive_data(cmd, 4, data, 2);
    *manuf_id = data[0];
    *device_id = data[1];
    return W25QXX_OK;
}

static w25qxx_status_t w25qxx_write_enable(void)
{
    uint8_t cmd[1] = {WRITE_ENABLE};

    w25qxx_send_data(cmd, 1, 0, 0);
    return W25QXX_OK;
}

static w25qxx_status_t w25qxx_write_disable(void)
{
    uint8_t cmd[1] = {WRITE_DISABLE};

    w25qxx_send_data(cmd, 1, 0, 0);
    return W25QXX_OK;
}

static w25qxx_status_t w25qxx_read_status_reg(uint8_t *reg_data)
{
    uint8_t cmd[1] = {READ_REG1};
    uint8_t data[1] = {0};

    w25qxx_receive_data(cmd, 1, data, 1);
    *reg_data = data[0];
    return W25QXX_OK;
}

static w25qxx_status_t w25qxx_write_status_reg(uint8_t reg_data)
{
    uint8_t cmd[1] = {WRITE_REG1};
    uint8_t data[1] = {reg_data};

    w25qxx_send_data(cmd, 1, data, 1);
    return W25QXX_OK;
}

static w25qxx_status_t w25qxx_is_busy(void)
{
    uint8_t status = 0;

    w25qxx_read_status_reg(&status);
    if (status & REG1_BUSY_MASK)
        return W25QXX_BUSY;
    return W25QXX_OK;
}

w25qxx_status_t w25qxx_sector_erase(uint32_t addr)
{
    uint8_t cmd[4] = {SECTOR_ERASE};

    cmd[1] = (uint8_t)(addr >> 16);
    cmd[2] = (uint8_t)(addr >> 8);
    cmd[3] = (uint8_t)(addr);
    w25qxx_write_enable();
    while (w25qxx_is_busy() == W25QXX_BUSY)
        ;
    w25qxx_send_data(cmd, 4, 0, 0);
    while (w25qxx_is_busy() == W25QXX_BUSY)
        ;
    return W25QXX_OK;
}

static w25qxx_status_t w25qxx_quad_page_program(uint32_t addr, uint8_t *data_buf, uint32_t length)
{
    uint8_t cmd[4] = {0};

    cmd[0] = PAGE_PROGRAM;
    cmd[1] = addr >> 16;
    cmd[2] = addr >> 8;
    cmd[3] = addr;
    w25qxx_write_enable();
    w25qxx_send_data(cmd, 4, data_buf, length);
    while (w25qxx_is_busy() == W25QXX_BUSY)
        ;
    return W25QXX_OK;
}

w25qxx_status_t w25qxx_write_data_direct(uint32_t addr, uint8_t *data_buf, uint32_t length)
{
    uint16_t pageremain;
    pageremain = 256 - addr % 256; //单页剩余的字节数
    if (length <= pageremain)
        pageremain = length; //不大于256个字节
    while (1)
    {
        w25qxx_quad_page_program(addr, data_buf, pageremain);
        if (length == pageremain)
            break; //写入结束了
        else       //NumByteToWrite>pageremain
        {
            data_buf += pageremain;
            addr += pageremain;

            length -= pageremain; //减去已经写入了的字节数
            if (length > 256)
                pageremain = 256; //一次可以写入256个字节
            else
                pageremain = length; //不够256个字节了
        }
    };
    return W25QXX_OK;
}

uint8_t W25QXX_BUFFER[4096];

w25qxx_status_t w25qxx_write_data(uint32_t addr, uint8_t *data_buf, uint32_t length)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t *W25QXX_BUF;
    W25QXX_BUF = W25QXX_BUFFER;
    secpos = addr / 4096;      //扇区地址
    secoff = addr % 4096;      //在扇区内的偏移
    secremain = 4096 - secoff; //扇区剩余空间大小
    if (length <= secremain)
        secremain = length; //不大于4096个字节
    while (1)
    {
        w25qxx_read_data(secpos * 4096, W25QXX_BUF, 4096); //读出整个扇区的内容
        for (i = 0; i < secremain; i++)                    //校验数据
        {
            if (W25QXX_BUF[secoff + i] != 0XFF)
                break; //需要擦除
        }
        if (i < secremain) //需要擦除
        {
            w25qxx_sector_erase(secpos);    //擦除这个扇区
            for (i = 0; i < secremain; i++) //复制
            {
                W25QXX_BUF[i + secoff] = data_buf[i];
            }
            w25qxx_write_data_direct(secpos * 4096, W25QXX_BUF, 4096); //写入整个扇区
        }
        else
            w25qxx_write_data_direct(addr, data_buf, secremain); //写已经擦除了的,直接写入扇区剩余区间.
        if (length == secremain)
            break; //写入结束了
        else       //写入未结束
        {
            secpos++;   //扇区地址增1
            secoff = 0; //偏移位置为0

            data_buf += secremain; //指针偏移
            addr += secremain;     //写地址偏移
            length -= secremain;   //字节数递减
            if (length > 4096)
                secremain = 4096; //下一个扇区还是写不完
            else
                secremain = length; //下一个扇区可以写完了
        }
    };
    return W25QXX_OK;
}

w25qxx_status_t w25qxx_read_data(uint32_t addr, uint8_t *data_buf, uint32_t length)
{
    uint8_t cmd[4] = {0};
    cmd[0] = READ_DATA;
    cmd[1] = addr >> 16;
    cmd[2] = addr >> 8;
    cmd[3] = addr;
    w25qxx_receive_data(cmd, 4, data_buf, length);
    return W25QXX_OK;
}

w25qxx_status_t w25qxx_init()
{
    spi_init(spi_bus_no, SPI_WORK_MODE_0, SPI_FF_STANDARD, DATALENGTH, 0);
    spi_set_clk_rate(SPI_DEVICE_0, 10000000);
    return W25QXX_OK;
}
