#ifndef _ADC_
#define _ADC_

class ADC
{
private:
    float V_x = 1;
    float I_x = 1;
    void TickV();
    void TickI();

public:
    ADC();
    void begin();
    void getV(uint16_t *data);
    void getI(uint16_t *data);
};

extern class ADC AD_ADC;

#endif