#include <Arduino.h>
#include <LCD/ULCD.h>
#include <IO.h>
#include <string.h>

ULCD LCD;

ULCD::ULCD()
{
}

void ULCD::begin()
{
    Serial1.begin(115200, LCD1, LCD2);
    NowKeyDown = NullKey;
}

void ULCD::SetPage(uint8_t page)
{
    Serial1.printf("page %d", page);
    Serial1.write(ff, 3);
}
void ULCD::UpDate(VI vi)
{
    Serial1.printf("x0.txt=%f.2ÿÿÿ", vi.SetV);
    Serial1.write(ff, 3);
}
KeyDown ULCD::GetKeyDown()
{
    return NowKeyDown;
}
void ULCD::SetIn(OnSet data)
{
}

void ULCD::Tick()
{
    for (int i = 0; i < 10; i++)
    {
        buff[i] = Serial1.read();
    }
    if (buff[0] != 0xff)
    {
        switch (buff[0])
        {
        case 0x21:
            NowKeyDown = Menu1;
            break;
        case 0x32:
            NowKeyDown = Menu2;
            NowSet.mode = buff[1];
            break;
        case 0x33:
            NowKeyDown = Menu3;
            break;
        }
    }
    Serial.write(buff, 10);
}

void ULCD::clear()
{
    NowKeyDown = NullKey;
    for (int i = 0; i < 10; i++)
    {
        buff[0] = 0x00;
    }
}
