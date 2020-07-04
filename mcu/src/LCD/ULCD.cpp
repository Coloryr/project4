#include <Arduino.h>
#include <LCD/ULCD.h>
#include <IO.h>

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
    Serial1.printf("page %dÿÿÿ", page);
}
void ULCD::UpDate(VI vi)
{
    Serial1.printf("x0.txt=%f.2ÿÿÿ", vi.SetV);
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
    Serial1.readBytes(buff, 10);
    if (buff[0] != 0x00)
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
    Serial1.print(buff);
}

void ULCD::clear()
{
    NowKeyDown = NullKey;
    for (int i = 0; i < 10; i++)
    {
        buff[0] = 0x00;
    }
}
