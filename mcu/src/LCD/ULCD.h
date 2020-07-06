#ifndef _ULCD_
#define _ULCD_

#include <DataS.h>
#include <Key/Key.h>

class ULCD
{
private:
    char buff[4] = {0xff};
    char ff[3] = {0xff, 0xff, 0xff};
    char data[6] = {0};
    KeyDown NowKeyDown;

public:
    ULCD();

    void clear();
    void begin();
    void Tick();

    void SetONOFF(bool on);
    void SetMode(bool mode);

    void UpSave(uint16_t data[3]);
    void SetBit(uint8_t pos);
    void SetPage(uint8_t page);
    void SetSave(uint16_t data);

    void UpDate(VI vi);
    void UpSet(VI vi);

    KeyDown GetKeyDown();

    void SetIn(OnSet data);
};

extern class ULCD LCD;

#endif