#ifndef _DATA_
#define _DATA_

#include <Arduino.h>
#include <DataS.h>

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  
//Mini STM32开发板使用的是24c02，所以定义EE_TYPE为AT24C02
#define EE_TYPE AT24C04

class DataSave
{
private:
    void SDA_OUT(void);
    void SDA_IN(void);
    uint8_t READ_SDA(void);
    void IIC_Start(void);                     //发送IIC开始信号
    void IIC_Stop(void);                      //发送IIC停止信号
    void IIC_Send_Byte(uint8_t txd);          //IIC发送一个字节
    uint8_t IIC_Read_Byte(unsigned char ack); //IIC读取一个字节
    uint8_t IIC_Wait_Ack(void);               //IIC等待ACK信号
    void IIC_Ack(void);                       //IIC发送ACK信号
    void IIC_NAck(void);                      //IIC不发送ACK信号

    void IIC_Write_One_Byte(uint8_t daddr, uint8_t addr, uint8_t data);
    uint8_t IIC_Read_One_Byte(uint8_t daddr, uint8_t addr);
    uint8_t write_buff[32] = {0x00, 0xff, 0x55, 0x67, 0x88};
    uint8_t read_buff[128] = {0};

public:
    DataSave();
    void begin();
    void SaveData(VI data);
    void GetData(VI *data);
    void SetSave(Mode mode, Local local, float data);
    void GetSave(Mode mode, Local local, float *data);
    void Remove(Mode mode, Local local);

    void WriteByte(uint8_t address, uint8_t data);
    void WritePage(uint8_t address, uint8_t *data, uint8_t length);
    uint8_t ReadByte(uint8_t address);
    void ReadPage(uint8_t address, uint8_t *data, uint8_t length);
};

extern class DataSave SaveData;

#endif