#include <Arduino.h>
#include <Tasks/TickTask.h>
#include <LCD/ULCD.h>
#include <Key/Key.h>
#include <DataS.h>
#include <Bilnk.h>

void TaskTick(void *pvParameters)
{
    LCD.Tick();
    KeyBoard.Tick();
    switch (LCD.GetKeyDown())
    {
    case Menu1:
        /* code */
        break;
    case Menu2:
        if (NowData->page == 0)
        {
            NowData->page = 1;
            NowData->mode = LCD.NowSet.mode;
            if (NowData->mode == 0)
            {
                Serial1.printf("t1.txt=Vÿÿÿ");
            }
            else
            {
                Serial1.printf("t1.txt=Iÿÿÿ");
            }
            break;
        }
        else if (NowData->page == 1)
        {
            /* code */
        }

    case Menu3:
        if (NowData->page == 0)
        {
            NowData->page = 2;
            NowData->mode = LCD.NowSet.mode;
            if (NowData->mode == 0)
            {
                Serial1.printf("t0.txt=%f.2ÿÿÿ", VaI->SetV);
            }
            else
            {
                Serial1.printf("t0.txt=%f.2ÿÿÿ", VaI->SetI);
            }
        }
        break;
    default:
        break;
    }
    if (LCD.GetKeyDown() != NullKey)
    {
        LCD.clear();
    }
}
