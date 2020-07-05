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
    w25qxx_read_data(0x40, data, 32);

    if (data[1] != write_buff[1])
    {
        Serial.println("init");
        w25qxx_write_data(0x40, write_buff, 32);
    }
    else
    {
        Serial.println("done");
    }
    free(data);
}

void DataSave::Save()
{
    uint8_t *data = (uint8_t *)malloc(4 * 6 * sizeof(uint8_t));
    DataTran tran;
    for (uint8_t i = 0; i < 3; i++)
    {
        tran.f = VSave[i];
        data[i * 4] = tran.u[0];
        data[i * 4 + 1] = tran.u[1];
        data[i * 4 + 2] = tran.u[2];
        data[i * 4 + 3] = tran.u[3];
    }
    for (uint8_t i = 0; i < 3; i++)
    {
        tran.f = ISave[i];
        data[i * 4 + 12] = tran.u[0];
        data[i * 4 + 13] = tran.u[1];
        data[i * 4 + 14] = tran.u[2];
        data[i * 4 + 15] = tran.u[3];
    }
    w25qxx_write_data(0x0a, data, 24);
    free(data);
}
void DataSave::Read()
{
    uint8_t *data = (uint8_t *)malloc(4 * 6 * sizeof(uint8_t));
    w25qxx_read_data(0x0a, data, 24);
    DataTran tran;
    for (uint8_t i = 0; i < 3; i++)
    {
        tran.u[0] = data[i * 4];
        tran.u[1] = data[i * 4 + 1];
        tran.u[2] = data[i * 4 + 2];
        tran.u[3] = data[i * 4 + 3];
        VSave[i] = tran.f;
    }
    for (uint8_t i = 0; i < 3; i++)
    {
        tran.u[0] = data[i * 4 + 12];
        tran.u[1] = data[i * 4 + 13];
        tran.u[2] = data[i * 4 + 14];
        tran.u[3] = data[i * 4 + 15];
        ISave[i] = tran.f;
    }
}

void DataSave::SaveData(VI data)
{
    uint8_t *a = (uint8_t *)malloc(8 * sizeof(uint8_t));
    DataTran tran;
    tran.f = data.SetV;
    for (int i = 0; i < 4; i++)
    {
        a[i] = tran.u[i];
    }
    tran.f = data.SetI;
    for (int i = 0; i < 4; i++)
    {
        a[i + 4] = tran.u[i];
    }
    w25qxx_write_data(0x00, a, 8);
    free(a);
}
void DataSave::GetData(VI *data)
{
    uint8_t *a = (uint8_t *)malloc(8 * sizeof(uint8_t));
    w25qxx_read_data(0x00, a, 8);
    DataTran tran;
    for (int i = 0; i < 4; i++)
    {
        tran.u[i] = a[i];
    }
    data->SetV = tran.f;
    for (int i = 0; i < 4; i++)
    {
        tran.u[i] = a[i + 4];
    }
    data->SetV = tran.f;
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