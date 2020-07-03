#ifndef _KEY_
#define _KEY_

#include <DataS.h>

class Key
{
private:
    KeyDown NowKeyDown;

public:
    Key();
    void Tick();
    KeyDown GetKey();
    void KeyClear();
    void KeyDo(KeyDown key);
};

extern class Key KeyBoard;

#endif