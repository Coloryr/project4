#include <Arduino.h>
#include <Tasks/TickTask.h>
#include <AD/DAC.h>
#include <Bell/Bell.h>
#include <FreeRTOS.h>
#include <task.h>
#include <LCD/ULCD.h>
#include <Key/Key.h>
#include <DataS.h>
#include <Bilnk.h>
#include <IO.h>

bool Cu()
{
    double temp = 0;
    switch (NowSet.StringLength)
    {
    case 1:
        temp += NowSet.Data[0];
        break;
    case 2:
        temp += NowSet.Data[0] * 10 + NowSet.Data[1];
        break;
    case 3:
        temp += NowSet.Data[0] * 100 + NowSet.Data[1] * 10 + NowSet.Data[2];
        break;
    case 4:
        temp += NowSet.Data[0] * 1000 + NowSet.Data[1] * 100 + NowSet.Data[2] * 10 + NowSet.Data[3];
        break;
    case 5:
        temp += NowSet.Data[0] * 10000 + NowSet.Data[1] * 1000 + NowSet.Data[2] * 100 + NowSet.Data[3] * 10 + NowSet.Data[4];
        break;
    }
    if (NowSet.PointLocal != 0)
    {
        temp = temp / pow(10, NowSet.StringLength - NowSet.PointLocal);
    }
    Serial.printf("f:%lf\n", temp);
    return temp <= (NowSet.mode == 0 ? 20 : 2);
}

void Set(uint8_t num)
{
    if (NowSet.StringLength == 5)
    {
        UBell.fail();
        return;
    }
    if (num == 10)
    {
        if (NowSet.PointLocal == 0)
        {
            UBell.fail();
            return;
        }
        else if (NowSet.StringLength - NowSet.PointLocal > 1)
        {
            UBell.fail();
            return;
        }
        else
        {
            NowSet.Data[NowSet.StringLength] = 0;
            NowSet.Data[NowSet.StringLength + 1] = 0;
            NowSet.StringLength += 2;
        }
    }
    else if (num == 11)
    {
        if (NowSet.StringLength == 0 || NowSet.PointLocal != 0)
        {
            UBell.fail();
            return;
        }
        else if ((NowSet.mode == 0 && NowSet.StringLength <= 2) || (NowSet.mode == 1 && NowSet.StringLength <= 1))
        {
            NowSet.PointLocal = NowSet.StringLength;
        }
        else
        {
            UBell.fail();
            return;
        }
    }
    else
    {
        if (NowSet.StringLength == 1 && NowSet.Data[0] == 0 && num == 0)
        {
            UBell.fail();
            return;
        }
        if (NowSet.StringLength - NowSet.PointLocal >= 3)
        {
            UBell.fail();
            return;
        }
        NowSet.Data[NowSet.StringLength] = num;
        NowSet.StringLength++;
        if (!Cu())
        {
            NowSet.StringLength--;
            NowSet.Data[NowSet.StringLength] = 0;
            UBell.fail();
            return;
        }
    }
    LCD.SetIn(NowSet);
}

void Delete()
{
    if (NowSet.StringLength == 0)
    {
        UBell.fail();
        return;
    }
    NowSet.Data[NowSet.StringLength] = 0;
    if (NowSet.PointLocal == NowSet.StringLength)
        NowSet.PointLocal = 0;
    else
        NowSet.StringLength--;
    LCD.SetIn(NowSet);
}

void Clear_()
{
    if (NowSet.StringLength == 0)
    {
        UBell.fail();
        return;
    }
    NowSet.StringLength = 0;
    NowSet.PointLocal = 0;
    for (uint8_t i = 0; i < 5; i++)
    {
        NowSet.Data[i] = 0;
    }
    LCD.SetIn(NowSet);
}

void ConfirmSet()
{
    double data = 0;
    switch (NowSet.StringLength)
    {
    case 1:
        data += NowSet.Data[0];
        break;
    case 2:
        data += NowSet.Data[0] * 10 + NowSet.Data[1];
        break;
    case 3:
        data += NowSet.Data[0] * 100 + NowSet.Data[1] * 10 + NowSet.Data[2];
        break;
    case 4:
        data += NowSet.Data[0] * 1000 + NowSet.Data[1] * 100 + NowSet.Data[2] * 10 + NowSet.Data[3];
        break;
    case 5:
        data += NowSet.Data[0] * 10000 + NowSet.Data[1] * 1000 + NowSet.Data[2] * 100 + NowSet.Data[3] * 10 + NowSet.Data[4];
        break;
    }
    if (NowSet.PointLocal != 0)
    {
        data = data / pow(10, NowSet.StringLength - NowSet.PointLocal);
    }
    data = data * 1000;
    if (NowSet.mode == 0)
    {
        VaI.SetV = data;
        AD_DAC.SetV(VaI.SetV);
    }
    else
    {
        VaI.SetI = data;
        AD_DAC.SetI(VaI.SetI);
    }
}

void TaskTick(void *pvParameters)
{
    Serial.println("Task Tick");
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        digitalWrite(ON, NowData.open);
        if (VaI.SetV >= 16000)
        {
            digitalWrite(SWI, LOW);
        }
        else
        {
            digitalWrite(SWI, HIGH);
        }
        if (VaI.NowV >= 20500 && VaI.NowI >= 2200)
        {
            digitalWrite(CUT, LOW);
            NowData.open = false;
        }
        else
        {
            digitalWrite(CUT, HIGH);
        }

        KeyBoard.KeyScan();
        switch (NowData.page)
        {
        case 0:
            switch (LCD.GetKeyDown())
            {
            case Menu1:
                /* code */
                break;
            case Menu2:
                NowData.page = 1;
                NowSet.mode = NowData.mode;
                NowSet.PointLocal = 0;
                NowSet.StringLength = 0;
                NowData.bit = 0;
                LCD.SetPage(NowData.page);
                LCD.SetMode(NowData.mode == 0 ? true : false);
                break;
            case Menu3:
                NowData.page = 2;
                NowSet.mode = NowData.mode;
                NowData.now = NowData.mode == 0 ? VaI.SetV : VaI.SetI;
                LCD.SetPage(NowData.page);
                break;
            case Mode1:
                NowData.mode = 0;
                break;
            case Mode2:
                NowData.mode = 1;
                break;
            case SetOFF:
                NowData.open = false;
                break;
            case SetON:
                NowData.open = true;
                break;
            default:
                break;
            }
            switch (KeyBoard.GetKey())
            {
            case Number1:
                break;
            default:
                break;
            }
            switch (KeyBoard.GetSpan())
            {
            case Next:
                if (NowData.mode == 0)
                {
                    switch (NowData.bit)
                    {
                    case 0:
                        if (VaI.SetV + 1 <= 20000)
                            VaI.SetV++;
                        break;
                    case 1:
                        if (VaI.SetV + 10 <= 20000)
                            VaI.SetV += 10;
                        break;
                    case 2:
                        if (VaI.SetV + 100 <= 20000)
                            VaI.SetV += 100;
                        break;
                    case 3:
                        if (VaI.SetV + 1000 <= 20000)
                            VaI.SetV += 1000;
                        break;
                    }
                    AD_DAC.SetV(VaI.SetV);
                }
                else
                {
                    switch (NowData.bit)
                    {
                    case 0:

                        if (VaI.SetI + 1 <= 2000)
                            VaI.SetI++;
                        break;
                    case 1:
                        if (VaI.SetI + 10 <= 2000)
                            VaI.SetI += 10;
                        break;
                    case 2:
                        if (VaI.SetI + 100 <= 2000)
                            VaI.SetI += 100;
                        break;
                    case 3:
                        if (VaI.SetI + 1000 >= 2000)
                            VaI.SetI += 1000;
                        break;
                    }
                    AD_DAC.SetI(VaI.SetI);
                }

                break;
            case Last:
                if (NowData.mode == 0)
                {
                    switch (NowData.bit)
                    {
                    case 0:
                        if (VaI.SetV - 1 >= 0)
                            VaI.SetV--;
                        break;
                    case 1:
                        if (VaI.SetV - 10 >= 0)
                            VaI.SetV -= 10;
                        break;
                    case 2:
                        if (VaI.SetV - 100 >= 0)
                            VaI.SetV -= 100;
                        break;
                    case 3:
                        if (VaI.SetV - 1000 >= 0)
                            VaI.SetV -= 1000;
                        break;
                    }
                    AD_DAC.SetV(VaI.SetV);
                }
                else
                {
                    switch (NowData.bit)
                    {
                    case 0:
                        if (VaI.SetI - 1 >= 0)
                            VaI.SetI--;
                        break;
                    case 1:
                        if (VaI.SetI - 10 >= 0)
                            VaI.SetI -= 10;
                        break;
                    case 2:
                        if (VaI.SetI - 100 >= 0)
                            VaI.SetI -= 100;
                        break;
                    case 3:
                        if (VaI.SetI - 1000 >= 0)
                            VaI.SetI -= 1000;
                        break;
                    }
                    AD_DAC.SetI(VaI.SetI);
                }
                break;
            case Down:
                NowData.bit++;
                if (NowData.bit == 4)
                    NowData.bit = 0;
                LCD.SetBit(NowData.bit);
                break;
            default:
                break;
            }
            break;
        case 1:
            switch (LCD.GetKeyDown())
            {
            case Back:
                NowData.page = 0;
                NowSet.mode = NowData.mode = 0;
                NowSet.PointLocal = 0;
                NowSet.StringLength = 0;
                NowData.now = 0;
                NowData.bit = 0;
                LCD.SetPage(NowData.page);
                LCD.SetBit(NowData.bit);
                break;
            case Number0:
                Set(0);
                break;
            case Number1:
                Set(1);
                break;
            case Number2:
                Set(2);
                break;
            case Number3:
                Set(3);
                break;
            case Number4:
                Set(4);
                break;
            case Number5:
                Set(5);
                break;
            case Number6:
                Set(6);
                break;
            case Number7:
                Set(7);
                break;
            case Number8:
                Set(8);
                break;
            case Number9:
                Set(9);
                break;
            case Number00:
                Set(10);
                break;
            case Point:
                Set(11);
                break;
            case Backspace:
                Delete();
                break;
            case Clear:
                Clear_();
                break;
            case Confirm:
                ConfirmSet();
                NowData.page = 0;
                NowSet.mode = NowData.mode = 0;
                NowSet.PointLocal = 0;
                NowSet.StringLength = 0;
                NowData.now = 0;
                NowData.bit = 0;
                NowSet.Data[0] = NowSet.Data[1] = NowSet.Data[2] = NowSet.Data[3] = NowSet.Data[4] = 0;
                LCD.SetPage(NowData.page);
                break;
            default:
                break;
            }
            break;
        case 2:
            switch (LCD.GetKeyDown())
            {
            case Back:
                NowData.page = 0;
                NowSet.mode = NowData.mode = 0;
                NowSet.PointLocal = 0;
                NowSet.StringLength = 0;
                NowData.now = 0;
                NowData.bit = 0;
                LCD.SetPage(NowData.page);
                LCD.SetBit(NowData.bit);
                break;
            default:
                break;
            }
            break;
        }
        LCD.clear();
        KeyBoard.KeyClear();
        vTaskDelayUntil(&xLastWakeTime, (50 / portTICK_RATE_MS));
    }
}
