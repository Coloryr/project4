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

void ULCD::UpSet(VI vi)
{
    Serial1.printf("x0.val=%d.3", vi.SetV);
    Serial1.write(ff, 3);
    Serial1.printf("x1.val=%d.3", vi.SetI);
    Serial1.write(ff, 3);
}
void ULCD::UpDate(VI vi)
{
    Serial1.printf("x2.val=%d.3", vi.NowV);
    Serial1.write(ff, 3);
    Serial1.printf("x3.val=%d.3", vi.NowI);
    Serial1.write(ff, 3);
}

void ULCD::UpSave(uint8_t data[3])
{
    Serial1.printf("x0.val=%d.3", data[0]);
    Serial1.write(ff, 3);
    Serial1.printf("x1.val=%d.3", data[1]);
    Serial1.write(ff, 3);
    Serial1.printf("x2.val=%d.3", data[2]);
    Serial1.write(ff, 3);
}

KeyDown ULCD::GetKeyDown()
{
    return NowKeyDown;
}
void ULCD::SetIn(OnSet data)
{
    Serial1.print("t0.txt=");
    Serial1.write(data.Data, data.StringLength);
    Serial1.write(ff, 3);
}

void ULCD::SetONOFF(bool on)
{
    Serial1.printf("bt0.val=%d.1", on);
    Serial1.write(ff, 3);
}

void ULCD::SetSave(uint8_t data)
{
    Serial1.printf("x3.val=%d.3", data);
    Serial1.write(ff, 3);
}

void ULCD::SetMode(bool mode)
{
    Serial1.print("t1.txt=");
    switch (mode)
    {
    case true:
        Serial1.print("\"V\"");
        break;
    case false:
        Serial1.print("\"I\"");
        break;
    }
    Serial1.write(ff, 3);
}

void ULCD::SetBit(uint8_t pos)
{
    Serial1.print("t0.txt=\"x1");
    for (int a = 0; a < pos; a++)
    {
        Serial1.print("0");
    }
    Serial1.print("\"");
    Serial1.write(ff, 3);
}

void ULCD::Tick()
{
    for (int i = 0; i < 2; i++)
    {
        buff[i] = Serial1.read();
    }
    if (buff[0] != 0xFF)
    {
        switch (buff[0])
        {
        case 0x41:
            NowKeyDown = Mode1;
            break;
        case 0x42:
            NowKeyDown = Mode2;
            break;
        case 0x43:
            NowKeyDown = Menu1;
            break;
        case 0x44:
            NowKeyDown = Menu2;
            break;
        case 0x45:
            NowKeyDown = Menu3;
            break;
        case 0x46:
            NowKeyDown = SetOFF;
            break;
        case 0x47:
            NowKeyDown = SetON;
            break;
        case 0x31:
            NowKeyDown = Number1;
            break;
        case 0x32:
            NowKeyDown = Number2;
            break;
        case 0x33:
            NowKeyDown = Number3;
            break;
        case 0x34:
            NowKeyDown = Number4;
            break;
        case 0x35:
            NowKeyDown = Number5;
            break;
        case 0x36:
            NowKeyDown = Number6;
            break;
        case 0x37:
            NowKeyDown = Number7;
            break;
        case 0x38:
            NowKeyDown = Number8;
            break;
        case 0x39:
            NowKeyDown = Number9;
            break;
        case 0x30:
            NowKeyDown = Number0;
            break;
        case 0x2F:
            NowKeyDown = Number00;
            break;
        case 0x2E:
            NowKeyDown = Point;
            break;
        case 0x2B:
            NowKeyDown = Backspace;
            break;
        case 0x2D:
            NowKeyDown = Clear;
            break;
        case 0x3D:
            NowKeyDown = SaveKey;
            break;
        case 0x2A:
            NowKeyDown = Confirm;
            break;
        case 0x58:
            NowKeyDown = Save1;
            break;
        case 0x59:
            NowKeyDown = Save2;
            break;
        case 0x5A:
            NowKeyDown = Save3;
            break;
        case 0x51:
            NowKeyDown = Back;
            break;
        }
    }
}

void ULCD::clear()
{
    NowKeyDown = NullKey;
    buff[0] = 0xFF;
}
