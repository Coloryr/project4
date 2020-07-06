#ifndef _ULCD_
#define _ULCD_

#include <DataS.h>
#include <Key/Key.h>

class ULCD
{
private:
    char buff[2] = {0xff, 0xff};
    char ff[3] = {0xff, 0xff, 0xff};
    KeyDown NowKeyDown;

public:
    OnSet NowSet;
    ULCD();

    void clear();
    void begin();
    void Tick();

    void SetONOFF(bool on);
    void SetMode(bool mode);

    void UpSave(uint8_t data[3]);
    void SetBit(uint8_t pos);
    void SetPage(uint8_t page);
    void SetSave(uint8_t data);

    void UpDate(VI vi);
    void UpSet(VI vi);

    KeyDown GetKeyDown();

    void SetIn(OnSet data);
};

extern class ULCD LCD;

#endif