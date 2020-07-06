#include <Arduino.h>
#include <Tasks/LCDTask.h>
#include <FreeRTOS.h>
#include <task.h>
#include <LCD/ULCD.h>
#include <Bilnk.h>

void TaskLCD(void *pvParameters)
{
    Serial.println("Task LCD");
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        LCD.Tick();
        if (NowData.page == 0)
        {
            LCD.UpDate(VaI);
        }
        else if (NowData.page == 2)
        {
            LCD.UpSave(NowData.mode == 0 ? VSave : ISave);
            LCD.SetSave(NowData.now);
        }
        // 使用当前时间初始化变量xLastWakeTime ,注意这和vTaskDelay()函数不同
        vTaskDelayUntil(&xLastWakeTime, (100 / portTICK_RATE_MS));
    }
}
