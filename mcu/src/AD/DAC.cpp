#include <Arduino.h>
#include <AD/DAC.h>
#include <DataS.h>
#include <IO.h>
#include <../../libraries/SPI/src/SPI.h>

DAC AD_DAC;

DAC::DAC()
{
}

void DAC::Write(uint8_t data)
{
    for (uint8_t mask = 0x80; mask; mask >>= 1)
    {
        digitalWrite(DAC_MISO, (data & mask) != 0);
        digitalWrite(DAC_SCK, HIGH);
        digitalWrite(DAC_SCK, LOW);
    }
}

void DAC::begin()
{
    pinMode(DAC_I_CS, OUTPUT);
    pinMode(DAC_V_CS, OUTPUT);
    pinMode(DAC_SCK, OUTPUT);
    pinMode(DAC_MISO, OUTPUT);

    digitalWrite(DAC_I_CS, HIGH);
    digitalWrite(DAC_V_CS, HIGH);
    digitalWrite(DAC_MISO, LOW);
    digitalWrite(DAC_SCK, LOW);

    _value =
        _register =
            _value1 =
                _register1 = 0;
}

void DAC::SetV(float data)
{
    _value = data * V_x;
    digitalWrite(DAC_V_CS, LOW);
    Write(_register);
    Write(_value >> 8);
    Write(_value & 0xFF);
    digitalWrite(DAC_V_CS, HIGH);
}

void DAC::SetI(float data)
{
    _value1 = data * I_x;
    digitalWrite(DAC_I_CS, LOW);
    Write(_register1);
    Write(_value1 >> 8);
    Write(_value1 & 0xFF);
    digitalWrite(DAC_I_CS, HIGH);
}