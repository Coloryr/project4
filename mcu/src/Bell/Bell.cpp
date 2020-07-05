#include <Arduino.h>
#include <Bell/Bell.h>
// #include <FreeRTOS.h>
// #include <task.h>
#include <IO.h>

Bell UBell;

Bell::Bell()
{
}

void Bell::begin()
{
    pinMode(BELL, OUTPUT);
    now = 0;
}

void Bell::bell()
{
    tone(BELL, 100000, 1000);
}

void Bell::error()
{
    tone(BELL, 200000, 1000);
}

void Bell::fail()
{
    tone(BELL, 50000, 1000);
}