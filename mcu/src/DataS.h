#ifndef _DATAS_
#define _DATAS_

#include <Arduino.h>

union DataTran1
{
    uint32_t u32;
    uint16_t u16[2];
};

union DataTran
{
    uint16_t u16;
    uint8_t u8[2];
};

struct VI
{
    uint16_t SetV = 0;
    uint16_t SetI = 0;
    uint16_t NowV = 0;
    uint16_t NowI = 0;
};

struct Now
{
    uint16_t now = 0;
    uint8_t mode = 0;
    uint8_t page = 0;
    uint8_t error = 0;
    uint8_t bit = 0;
    bool open = false;
};

struct OnSet
{
    uint8_t mode = false;
    uint8_t PointLocal = 0;
    uint8_t StringLength = 0;
    char Data[5] = {0};
};

enum Mode
{
    V = 0,
    I = 1
};

enum Local
{
    S1 = 0,
    S2 = 1,
    S3 = 2
};

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
    Number00,
    Point,
    //编码轮 左右中
    Last,
    Next,
    Down,
    //预设 保存1-3 加载1-3
    Save1,
    Save2,
    Save3,
    Load1,
    Load2,
    Load3,
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
    //打开电源，关闭电源
    SetON,
    SetOFF,
    //空按键
    NullKey
};

#endif