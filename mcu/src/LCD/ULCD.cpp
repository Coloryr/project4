#include <LCD/ULCD.h>

ULCD LCD;

ULCD::ULCD()
{
}

void ULCD::begin()
{
    Serial1.begin(112500, 10, 11);
}

void ULCD::SetPage(uint8_t page)
{
    Serial1.printf("page " + (0x30 + page));
}
void ULCD::UpDate(VI vi)
{
    
}
KeyDown ULCD::GetKeyDown()
{
}
void ULCD::SetIn(OnSet data)
{
}
