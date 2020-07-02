#ifndef _DATA_
#define _DATA_

#include <Arduino.h>
#include <DataS.h>

#define I2C_WR 0
#define I2C_RD 1

#define ADDRESS 0xA0

class DataSave
{
private:
    void WriteByte(int address, uint8_t data);
    void WritePage(int eeaddr, uint8_t *data, uint8_t length);
    uint8_t ReadByte(int address);
    void ReadPage(int eeaddr, uint8_t *data, uint8_t length);
    uint8_t write_buff[3] = {0, 0, 0};
    uint8_t read_buff[2] = {0, 0};
public:
    DataSave();
    void begin();
    void SaveData(VI data);
    void GetData(VI *data);
    void SetSave(Mode mode, Local local, float data);
    void GetSave(Mode mode, Local local, float *data);
    void Remove(Mode mode, Local local);
};

extern class DataSave SaveData;

#endif