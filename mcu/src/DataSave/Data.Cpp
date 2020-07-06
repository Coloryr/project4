#include <DataSave/Data.h>
#include <IO.h>
#include <DataS.h>
#include <DataSave/w25qxx.h>
#include <Bilnk.h>
#include <../../../libraries/SPI/src/SPI.h>

DataSave SaveData;

DataSave::DataSave()
{
}

void DataSave::begin()
{
    uint8_t temp, temp1;
    fpioa_set_function(SPI_SCK, FUNC_SPI0_SCLK);
    fpioa_set_function(SPI_MOSI, FUNC_SPI0_D0);
    fpioa_set_function(SPI_MISO, FUNC_SPI0_D1);
    fpioa_set_function(SPI_CS, FUNC_SPI0_SS0);

    w25qxx_init();
    w25qxx_read_id(&temp, &temp1);
    Serial.printf("ID:0x%02x%02x\n", temp, temp1);
    uint8_t *data = (uint8_t *)malloc(32 * sizeof(uint8_t));
    w25qxx_read_data(0x50, data, 32);

    if (data[1] != write_buff[1])
    {
        Serial.println("init");
        w25qxx_write_data(0x50, write_buff, 32);
        w25qxx_write_data(0x00, read_buff, 32);
    }
    else
    {
        Serial.println("done");
    }
    free(data);
}

void DataSave::Save()
{
    uint8_t *data = (uint8_t *)malloc(2 * 6 * sizeof(uint8_t));
    DataTran tran;
    for (uint8_t i = 0; i < 3; i++)
    {
        tran.u16 = VSave[i];
        data[i * 2] = tran.u8[0];
        data[i * 2 + 1] = tran.u8[1];
    }
    for (uint8_t i = 0; i < 3; i++)
    {
        tran.u16 = ISave[i];
        data[i * 2 + 6] = tran.u8[0];
        data[i * 2 + 6] = tran.u8[1];
    }
    w25qxx_write_data(0x0a, data, 12);
    free(data);
}
void DataSave::Read()
{
    uint8_t *data = (uint8_t *)malloc(2 * 6 * sizeof(uint8_t));
    w25qxx_read_data(0x0a, data, 12);
    DataTran tran;
    for (uint8_t i = 0; i < 3; i++)
    {
        tran.u8[0] = data[i * 2];
        tran.u8[1] = data[i * 2 + 1];
        VSave[i] = tran.u16;
    }
    for (uint8_t i = 0; i < 3; i++)
    {
        tran.u8[0] = data[i * 2 + 6];
        tran.u8[1] = data[i * 2 + 6];
        ISave[i] = tran.u16;
    }
}

void DataSave::SaveData(VI *data)
{
    uint8_t *a = (uint8_t *)malloc(4 * sizeof(uint8_t));
    DataTran tran;
    tran.u16 = data->SetV;
    for (int i = 0; i < 2; i++)
    {
        a[i] = tran.u8[i];
    }
    tran.u16 = data->SetI;
    for (int i = 0; i < 2; i++)
    {
        a[i + 2] = tran.u8[i];
    }
    w25qxx_write_data(0x00, a, 4);
    free(a);
}
void DataSave::GetData(VI *data)
{
    uint8_t *a = (uint8_t *)malloc(4 * sizeof(uint8_t));
    w25qxx_read_data(0x00, a, 4);
    DataTran tran;
    for (int i = 0; i < 2; i++)
    {
        tran.u8[i] = a[i];
    }
    data->SetV = tran.u16;
    for (int i = 0; i < 2; i++)
    {
        tran.u8[i] = a[i + 2];
    }
    data->SetV = tran.u16;
    free(a);
}

void DataSave::Clear()
{
    for (uint8_t i = 0; i < 3; i++)
    {
        VSave[i] = 0;
        ISave[i] = 0;
    }
    uint8_t *a = (uint8_t *)malloc(4 * 6 * sizeof(uint8_t));
    for (uint8_t i = 0; i < 24; i++)
    {
        a[i] = 0;
    }
    w25qxx_write_data(0x0a, a, 24);
    free(a);
}