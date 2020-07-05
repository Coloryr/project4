#ifndef _ADC_
#define _ADC_

class ADC
{
private:
    double V_x = 1;
    double I_x = 1;
    void TickV();
    void TickI();

public:
    ADC();
    void begin();
    void getV(float *data);
    void getI(float *data);
};

extern class ADC AD_ADC;

#endif