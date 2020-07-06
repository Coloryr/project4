#ifndef _BELL_
#define _BELL_

#include <Arduino.h>

class Bell
{
private:
    uint8_t now;
    bool isBell;

public:
    Bell();
    void begin();
    void bell();
    void error();
    void fail();
};

extern class Bell UBell;

#endif