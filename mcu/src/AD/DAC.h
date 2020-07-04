#ifndef _DAC_
#define _DAC_

class DAC
{
private:
    uint16_t _value;
    uint8_t _register;
    uint16_t _value1;
    uint8_t _register1;

    float V_x = 1;
    float I_x = 1;

    void Write(uint8_t data);

public:
    DAC();
    void begin();
    void SetV(float data);
    void SetI(float data);
};

extern class DAC AD_DAC;

#endif