#ifndef _DATAS_
#define _DATAS_

#include <Arduino.h>

union DataTran
{
    float f;
    uint8_t u[4];
};

union Address
{
    unsigned long i;
    uint8_t u[2];
};

struct VI
{
    float SetV = 0;
    float SetI = 0;
    float NowV = 0;
    float NowI = 0;
};

struct Now
{
    uint8_t mode = 0;
    uint8_t page = 0;
    uint8_t error = 0;
    bool open = false;
};

struct OnSet
{
    bool mode;
    uint8_t PointLocal;
    uint8_t StringLength;
    float Val;
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

#endif