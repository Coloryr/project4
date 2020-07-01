#include <DataSave/Data.h>
#include <Wire.h>
#include <IO.h>
#include <DataS.h>
#include <kendryte-standalone-sdk/lib/drivers/include/i2c.h>

DataSave SaveData;

DataSave::DataSave()
{
}

void DataSave::begin()
{
    Wire.begin(I2C_SDA, I2C_SCL, (uint32_t)500000);
}

void DataSave::WriteByte(int address, uint8_t data)
{
    volatile i2c_t *i2c_adapter = i2c[I2C_DEVICE_0];
    i2c_adapter->tar = I2C_TAR_ADDRESS(ADDRESS | I2C_WR);

    Address addr;
    addr.i = address;
    write_buff[0] = addr.u[0];
    write_buff[1] = addr.u[1];
    write_buff[2] = data;
    i2c_send_data(I2C_DEVICE_0, write_buff, 3);
}
void DataSave::WritePage(int address, uint8_t *data, uint8_t length)
{
    volatile i2c_t *i2c_adapter = i2c[I2C_DEVICE_0];
    i2c_adapter->tar = I2C_TAR_ADDRESS(I2C_SDA);

    Address addr;
    addr.i = address;
    uint8_t *a = (uint8_t *)malloc((2 + length) * sizeof(uint8_t));
    a[0] = addr.u[0];
    a[1] = addr.u[1];
    for (int i = 0; i < length; i++)
    {
        a[i + 2] = data[i];
    }
    i2c_send_data(I2C_DEVICE_0, a, 2 + length);
    free(a);
}
uint8_t DataSave::ReadByte(int address)
{
    volatile i2c_t *i2c_adapter = i2c[I2C_DEVICE_0];
    i2c_adapter->tar = I2C_TAR_ADDRESS(0xA1);

    Address addr;
    addr.i = address;
    read_buff[0] = addr.u[0];
    read_buff[1] = addr.u[1];

    uint8_t data = 0;

    i2c_recv_data(I2C_DEVICE_0, read_buff, 2, &data, 1);
    return data;
}
void DataSave::ReadPage(int address, uint8_t *data, uint8_t length)
{
    volatile i2c_t *i2c_adapter = i2c[I2C_DEVICE_0];
    i2c_adapter->tar = I2C_TAR_ADDRESS(0xA1);

    Address addr;
    addr.i = address;
    read_buff[0] = addr.u[0];
    read_buff[1] = addr.u[1];

    i2c_recv_data(I2C_DEVICE_0, read_buff, 2, data, length);
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
    WritePage(0x00, a, 8);
    free(a);
}
void DataSave::GetData(VI *data)
{
    uint8_t *a = (uint8_t *)malloc(8 * sizeof(uint8_t));
    ReadPage(0x00, a, 8);
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
void DataSave::SetSave(Mode mode, Local local, float data)
{
    switch (mode)
    {
    case V:
        DataTran tran;
        tran.f = data;
        WritePage(0x10 + local, tran.u, 4);
        break;
    case I:
        DataTran tran;
        tran.f = data;
        WritePage(0x20 + local, tran.u, 4);
        break;
    }
}
void DataSave::GetSave(Mode mode, Local local, float *data)
{
    switch (mode)
    {
    case V:
        DataTran tran;
        ReadPage(0x10 + local, tran.u, 4);
        data[0] = tran.f;
        break;
    case I:
        DataTran tran;
        ReadPage(0x20 + local, tran.u, 4);
        data[0] = tran.f;
        break;
    }
}
void DataSave::Remove(Mode mode, Local local)
{
    uint8_t a[] = {0, 0, 0, 0};
    switch (mode)
    {
    case V:
        WritePage(0x10 + local, a, 4);
        break;
    case I:
        Data tran;
        WritePage(0x20 + local, a, 4);
        break;
    }
}