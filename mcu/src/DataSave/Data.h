#ifndef _DATA_
#define _DATA_

#include <Arduino.h>
#include <DataS.h>

class DataSave
{
private:
    uint8_t write_buff[32] = {0x00, 0xff, 0x55, 0x67, 0x88};
    uint8_t read_buff[32] = {0x00};

public:
    DataSave();
    void begin();
    void SaveData(VI* data);
    void GetData(VI* data);
    void Save();
    void Read();
    void Clear();
};

extern class DataSave SaveData;

#endif