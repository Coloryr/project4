#ifndef _ULCD_
#define _ULCD_

#include <Arduino.h>
#include <DataS.h>
#include <Key/Key.h>

typedef struct OnSet
{
    bool mode;
    uint8_t PointLocal;
    uint8_t StringLength;
    float Val;
};

class ULCD
{
private:
    OnSet NowSet;
public:
    KeyDown NowKeyDown;
    ULCD();
    void begin();
    void SetPage(uint8_t page);
    void UpDate(VI vi);
    KeyDown GetKeyDown();
    void SetIn(OnSet data);
};

#endif