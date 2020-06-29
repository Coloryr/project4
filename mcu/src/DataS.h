#ifndef DATAS_H
#define DATAS_H

#include <Arduino.h>

typedef struct VI
{
    float SetV = 0;
    float SetI = 0;
    float NowV = 0;
    float NowI = 0;
};

typedef struct Now
{
    uint8_t mode = 0;
    uint8_t page = 0;
    uint8_t error = 0;
    bool open = false;
};

#endif