#include <Arduino.h>
#include <Tasks/TickTask.h>
#include <FreeRTOS.h>
#include <task.h>
#include <LCD/ULCD.h>
#include <Key/Key.h>
#include <DataS.h>
#include <Bilnk.h>

void TaskTick(void *pvParameters)
{
    Serial.println("Task Tick");
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
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
                LCD.NowSet.mode = NowData.mode;
                LCD.NowSet.PointLocal = 0;
                LCD.NowSet.StringLength = 0;
                LCD.NowSet.Val = 0;
                LCD.SetMode(NowData.mode == 0 ? true : false);
                break;
            case Menu3:
                NowData.page = 2;
                LCD.NowSet.mode = NowData.mode;
                LCD.SetSave(NowData.mode == 0 ? VaI.SetV : VaI.SetI);
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
                Serial.println("Next");
                break;
            case Down:
                Serial.println("Down");
                break;
            default:
                break;
            }
            break;
        }
        LCD.clear();
        KeyBoard.KeyClear();
        vTaskDelayUntil(&xLastWakeTime, (100 / portTICK_RATE_MS));
    }
}
