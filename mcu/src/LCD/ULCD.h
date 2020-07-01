#ifndef _ULCD_
#define _ULCD_

#include <DataS.h>
#include <Key/Key.h>

class ULCD
{
private:
    char buff[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    KeyDown NowKeyDown;

public:
    OnSet NowSet;
    ULCD();
    void clear();
    void begin();
    void SetPage(uint8_t page);
    void UpDate(VI vi);
    KeyDown GetKeyDown();
    void SetIn(OnSet data);
    void Tick();
};
 
extern class ULCD LCD;

#endif