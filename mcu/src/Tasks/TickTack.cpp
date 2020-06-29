#include <Arduino.h>
#include <ALL.h>

#include <Tasks/TickTask.h>

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
        if (NowData.page == 0)
        {
            NowData.page = 1;
            NowData.mode = LCD.NowSet.mode;
            if (NowData.mode == 0)
            {
                Serial1.printf("t1.txt=V");
            }
            else
            {
                Serial1.printf("t1.txt=I");
            }
            break;
        }
        else if (NowData.page == 1)
        {
            /* code */
        }

    case Menu3:
        if (NowData.page == 0)
        {
            NowData.page = 2;
            NowData.mode = LCD.NowSet.mode;
            if(NowData.mode == 0)
            {
                Serial1.printf("t0.txt=%d.2", VaI.SetV);
            }
            else
            {
                Serial1.printf("t0.txt=%d.2", VaI.SetI);
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
