#ifndef KEY_H
#define KEY_H

#include <Arduino.h>

#define KA 18
#define KB 19
#define KC 20
#define KD 21
#define K1 22
#define K2 23
#define K3 24
#define K4 25

#define B1 26
#define B2 27
#define BA 28

enum KeyDown
{
    //数字 0-9
    Number1,
    Number2,
    Number3,
    Number4,
    Number5,
    Number6,
    Number7,
    Number8,
    Number9,
    Number0,
    Point,
    //编码轮 左右中
    Last,
    Next,
    Down,
    //预设 保存1-3 删除1-3
    Save1,
    Save2,
    Save3,
    Delete1,
    Delete2,
    Delete3,
    //功能选择
    Mode1,
    Mode2,
    //菜单
    Menu1,
    Menu2,
    Menu3,
    //清空，退格，返回，确认，保存
    Clear,
    Backspace,
    Back,
    Confirm,
    SaveKey,
    NullKey
};

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

#endif