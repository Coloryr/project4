#include <Arduino.h>
#include <AD/ADC.h>
#include <DataS.h>
#include <IO.h>

ADC AD_ADC;

ADC::ADC()
{
}

void ADC::TickV()
{
    digitalWrite(ADC_V_SCK, LOW);
    delayMicroseconds(2);
    digitalWrite(ADC_V_SCK, HIGH);
}

void ADC::TickI()
{
    digitalWrite(ADC_I_SCK, LOW);
    delayMicroseconds(2);
    digitalWrite(ADC_I_SCK, HIGH);
}
void ADC::begin()
{
    pinMode(ADC_MISO, INPUT_PULLUP);
    pinMode(ADC_V_SCK, OUTPUT);
    pinMode(ADC_I_SCK, OUTPUT);
}

void ADC::getV(float *data)
{
    uint32_t value = 0;
    for (int i = 0; i < 24; ++i)
    {
        TickV();
        value |= !!digitalRead(ADC_MISO);
        value <<= 1;
    }
    TickV();
    TickV();
    TickV();
    DataTran2 tran;
    tran.u32 = value;

    data[0] = (float)tran.f * V_x;
}
void ADC::getI(float *data)
{
    uint32_t value = 0;
    for (int i = 0; i < 24; ++i)
    {
        TickI();
        value |= !!digitalRead(ADC_MISO);
        value <<= 1;
    }
    TickI();
    TickI();
    TickI();
    DataTran2 tran;
    tran.u32 = value;

    data[0] = (float)tran.f * V_x;
}