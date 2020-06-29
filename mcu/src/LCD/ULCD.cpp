#include <LCD/ULCD.h>
#include <ALL.h>

ULCD LCD;

ULCD::ULCD()
{
}

void ULCD::begin()
{
    Serial1.begin(112500, 10, 11);
    buff = (char *)malloc(10 * sizeof(char));
    NowData.page = 0;
    NowKeyDown = NullKey;
}

void ULCD::SetPage(uint8_t page)
{
    Serial1.printf("page " + (0x30 + page));
}
void ULCD::UpDate(VI vi)
{
    char *a;
    Serial1.printf("x0.txt=%d.2", vi.SetV);
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
}

void ULCD::clear()
{
    NowKeyDown = NullKey;
    for (int i = 0; i < 10; i++)
    {
        buff[0] = 0x00;
    }
}
