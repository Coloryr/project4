#ifndef _ULCD_
#define _ULCD_

#include <DataS.h>
#include <Key/Key.h>

class ULCD
{
private:
    char buff[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    KeyDown NowKeyDown;
    char ff[3] = {0xff, 0xff, 0xff};

public:
    OnSet NowSet;
    ULCD();
    void clear();
    void begin();
    void SetON(bool on);
    void SetMode(bool mode);
    void SetPage(uint8_t page);
    void UpDate(VI vi);
    void SetSave(float data);
    KeyDown GetKeyDown();
    void SetIn(OnSet data);
    void Tick();
};

extern class ULCD LCD;

#endif