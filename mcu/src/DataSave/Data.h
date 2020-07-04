#ifndef _DATA_
#define _DATA_

#include <Arduino.h>
#include <DataS.h>

union DataTran1
{
    uint8_t u8[2];
    uint16_t u16;
};

class DataSave
{
private:
    uint8_t write_buff[32] = {0x00, 0xff, 0x55, 0x67, 0x88};
    uint8_t read_buff[128] = {0xff};

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