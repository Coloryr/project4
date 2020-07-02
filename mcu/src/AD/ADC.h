#ifndef _ADC_
#define _ADC_

class ADC
{
private:

public:
    ADC();
    void begin();
    void getV(float* data);
    void getI(float* data);
};

extern class ADC AD_ADC;

#endif