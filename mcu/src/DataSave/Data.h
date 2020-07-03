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