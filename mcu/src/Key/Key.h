#ifndef _KEY_
#define _KEY_

#include <DataS.h>
#include <Arduino.h>

class Key
{
private:
    KeyDown NowKeyDown;
    KeyDown SpanDown;
    int B1_Last;
    int B2_Last;

public:
    Key();
    void KeyScan();
    void SpanScan();
    KeyDown GetKey();
    KeyDown GetSpan();
    void KeyClear();
    void KeyDo(KeyDown key);
};

extern class Key KeyBoard;

#endif