#ifndef DATA_H
#define DATA_H

#include <DataS.h>

#define ID_ADDR 0xA0
#define PAGE_SIZE 64
#define SIZE (16 * 1024)
#define ADDR_BYTES 2

#define I2C_WR 0
#define I2C_RD 1

union Data {
    float f;
    uint8_t u[4];
};

union Address {
    unsigned long i;
    uint8_t u[2];
};

enum Mode
{
    V = 0,
    I = 1
};

enum Local
{
    S1 = 0,
    S2 = 1,
    S3 = 2
};

class DataSave
{
private:
    void WriteByte(int address, uint8_t data);
    void WritePage(int eeaddr, uint8_t *data, uint8_t length);
    uint8_t ReadByte(int address);
    void ReadPage(int eeaddr, uint8_t *data, uint8_t length);

public:
    DataSave();
    void begin();
    void SaveData(VI data);
    void GetData(VI *data);
    void SetSave(Mode mode, Local local, float data);
    void GetSave(Mode mode, Local local, float *data);
    void Remove(Mode mode, Local local);
};

#endif