#include <Arduino.h>
#include <AD/ADC.h>
#include <DataS.h>
#include <IO.h>

ADC AD_ADC;

ADC::ADC()
{
}

void ADC::begin()
{
    pinMode(ADC_MISO, INPUT);
}

void ADC::getV(float *data)
{
}
void ADC::getI(float *data)
{
}