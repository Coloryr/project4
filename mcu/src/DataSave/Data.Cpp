#include <DataSave/Data.h>
#include <Wire.h>

DataSave Save;

DataSave::DataSave()
{
}

void DataSave::WriteByte(uint8_t deviceaddress, int address, uint8_t data)
{
    uint8_t devaddr = deviceaddress | ((address >> 8) & 0x07);
    Address addr;
    addr.i = address;
    Wire.beginTransmission(devaddr);
    Wire.write(addr.u, 2);
    Wire.write(data);
    Wire.endTransmission(false);
}
void DataSave::WritePage(uint8_t deviceaddress, int address,
                         const uint8_t *data, uint8_t length)
{
    uint8_t devaddr = deviceaddress | ((address >> 8) & 0x07);
    uint8_t addr = address;
    Wire.beginTransmission(devaddr);
    Wire.write(addr);
    for (int i = 0; i < length; i++)
    {
        Wire.write(data[i]);
    }
    Wire.endTransmission();
}
uint8_t DataSave::ReadByte(uint8_t deviceaddress, int address)
{
    uint8_t rdata = -1;
    uint8_t devaddr = deviceaddress | ((address >> 8) & 0x07);
    uint8_t addr = address;

    Wire.beginTransmission(devaddr);
    Wire.write(addr);
    Wire.endTransmission();
    Wire.requestFrom(int(devaddr), 1);
    if (Wire.available())
    {
        rdata = Wire.read();
    }
    return rdata;
}
void DataSave::ReadPage(uint8_t deviceaddress, int eeaddr,
                        const uint8_t *data, uint8_t length)
{
}

void DataSave::begin()
{
    Wire.begin(12, 13, (uint32_t)500000);
}

void DataSave::SaveData(VI data)
{
    Data tran;
    tran.f = data.SetV;
    Wire.writeTransmission(ID_ADDR | I2C_WR, tran.u, 4, true);
    tran.f = data.SetI;
    Wire.writeTransmission(0x04, tran.u, 4, true);
    Wire.endTransmission(false);
}
void DataSave::GetData(VI *data)
{
    Data tran;
    Wire.readTransmission(ID_ADDR | I2C_RD, tran.u, 4, true);
    data->SetV = tran.f;
    Wire.readTransmission(0x04, tran.u, 4, true);
    data->SetV = tran.f;
    Wire.endTransmission(false);
}
void DataSave::SetSave(Mode mode, Local local, float data)
{
    switch (mode)
    {
    case V:
        Wire.beginTransmission(ID_ADDR | I2C_WR);
        Data tran;
        tran.f = data;
        Wire.writeTransmission(0x10 + (local * 4), tran.u, 4, true);
        Wire.endTransmission(false);
        break;
    case I:
        break;
    }
}
void DataSave::GetSave(Mode mode, Local local, float *data)
{
}
void DataSave::Remove(Mode mode, Local local)
{
}