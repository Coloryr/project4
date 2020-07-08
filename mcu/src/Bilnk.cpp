#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <Tasks/TickTask.h>
#include <Tasks/ADCTask.h>
#include <Tasks/LCDTask.h>
#include <Tasks/SpanTask.h>
#include <DataS.h>
#include <LCD/ULCD.h>
#include <AD/ADC.h>
#include <AD/DAC.h>
#include <DataSave/Data.h>
#include <Bilnk.h>
#include <IO.h>

VI VaI;
Now NowData;
OnSet NowSet;

uint16_t VSave[3];
uint16_t ISave[3];

void TaskStart()
{

    xTaskCreate(
        TaskLCD,
        (const portCHAR *)"LCD",
        128,
        NULL,
        2,
        NULL);

    xTaskCreate(
        TaskADC,
        (const portCHAR *)"ADC",
        128,
        NULL,
        2,
        NULL);

    xTaskCreate(
        TaskTick,
        (const portCHAR *)"Tick",
        128,
        NULL,
        2,
        NULL);

    xTaskCreate(
        TaskSpan,
        (const portCHAR *)"Span",
        128,
        NULL,
        2,
        NULL);
}

void init()
{
    NowData.mode = 0;
    NowData.error = 0;
    NowData.open = false;
    NowData.page = 0;
    NowData.now =0;

    pinMode(ON, OUTPUT);
    pinMode(CUT, OUTPUT);
    pinMode(SWI, OUTPUT);

    digitalWrite(SWI, LOW);
    digitalWrite(ON, LOW);

    SaveData.GetData(&VaI);

    VaI.NowI = 0;
    VaI.NowV = 0;
}

void setup()
{
    Serial.begin(115200);
    LCD.begin();
    SaveData.begin();
    AD_ADC.begin();
    AD_DAC.begin();

    init();

    TaskStart();
    LCD.SetPage(0);
    Serial.printf("hello world");
    vTaskStartScheduler();
    
}

void loop()
{
}
