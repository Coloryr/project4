#include <Arduino.h>
#include <Key/Key.h>
#include <IO.h>
#include <FreeRTOS.h>
#include <task.h>

Key KeyBoard;

/*
 1 2 3 ←
 4 5 6 Clear
 7 8 9 Save
 . 0 确认 Back
*/
/*
 x x x ON
 x x x OFF
 x x x Menu
 x x Save Set
*/
/*
 L1 L2 L3 x
 S1 S2 S3 x
 x x x x
 x x x Back
*/

Key::Key()
{
    pinMode(KA, OUTPUT);
    pinMode(KB, OUTPUT);
    pinMode(KC, OUTPUT);
    pinMode(KD, OUTPUT);

    pinMode(K1, INPUT_PULLUP);
    pinMode(K2, INPUT_PULLUP);
    pinMode(K3, INPUT_PULLUP);
    pinMode(K4, INPUT_PULLUP);

    pinMode(B1, INPUT_PULLUP);
    pinMode(B2, INPUT_PULLUP);
    pinMode(BA, INPUT_PULLUP);

    digitalWrite(KA, HIGH);
    digitalWrite(KB, HIGH);
    digitalWrite(KC, HIGH);
    digitalWrite(KD, HIGH);
    digitalWrite(B1, HIGH);
    digitalWrite(B2, HIGH);
    digitalWrite(BA, HIGH);

    NowKeyDown = NullKey;
    SpanDown = NullKey;

    B1_Last = B2_Last = GPIO_PV_HIGH;
}

void Key::KeyScan()
{
    digitalWrite(KA, LOW);
    delayMicroseconds(10);
    if (digitalRead(K1) == LOW)
    {
        NowKeyDown = Number1;
    }
    else if (digitalRead(K2) == LOW)
    {
        NowKeyDown = Number2;
    }
    else if (digitalRead(K3) == LOW)
    {
        NowKeyDown = Number3;
    }
    else if (digitalRead(K4) == LOW)
    {
        NowKeyDown = Backspace;
    }
    digitalWrite(KA, HIGH);
    digitalWrite(KB, LOW);
    delayMicroseconds(10);
    if (digitalRead(K1) == LOW)
    {
        NowKeyDown = Number4;
    }
    else if (digitalRead(K2) == LOW)
    {
        NowKeyDown = Number5;
    }
    else if (digitalRead(K3) == LOW)
    {
        NowKeyDown = Number6;
    }
    else if (digitalRead(K4) == LOW)
    {
        NowKeyDown = Clear;
    }
    digitalWrite(KB, HIGH);
    digitalWrite(KC, LOW);
    delayMicroseconds(10);
    if (digitalRead(K1) == LOW)
    {
        NowKeyDown = Number7;
    }
    else if (digitalRead(K2) == LOW)
    {
        NowKeyDown = Number8;
    }
    else if (digitalRead(K3) == LOW)
    {
        NowKeyDown = Number9;
    }
    else if (digitalRead(K4) == LOW)
    {
        NowKeyDown = SaveKey;
    }
    digitalWrite(KC, HIGH);
    digitalWrite(KD, LOW);
    delayMicroseconds(10);
    if (digitalRead(K1) == LOW)
    {
        NowKeyDown = Point;
    }
    else if (digitalRead(K2) == LOW)
    {
        NowKeyDown = Number0;
    }
    else if (digitalRead(K3) == LOW)
    {
        NowKeyDown = Confirm;
    }
    else if (digitalRead(K4) == LOW)
    {
        NowKeyDown = Back;
    }
    while (digitalRead(K1) != HIGH)
    {
        vTaskDelay(200 / portTICK_RATE_MS);
    }
    while (digitalRead(K2) != HIGH)
    {
        vTaskDelay(200 / portTICK_RATE_MS);
    }
    while (digitalRead(K3) != HIGH)
    {
        vTaskDelay(200 / portTICK_RATE_MS);
    }
    while (digitalRead(K4) != HIGH)
    {
        vTaskDelay(200 / portTICK_RATE_MS);
    }
}

void Key::SpanScan()
{
    int B1_now = digitalRead(B1);
    int B2_now = digitalRead(B2);
    int BA_now = digitalRead(BA);
    if (B1_now != B1_Last)
    {
        if (B1_now == HIGH)
        {
            if ((B1_Last == HIGH) && (B2_now == LOW))
                SpanDown = Next;
            else if ((B1_Last == LOW) && (B2_now == HIGH))
                SpanDown = Last;
            else if ((B2_Last == B2_now) && (B2_now == LOW))
                SpanDown = Next;
            else if ((B2_Last == B2_now) && (B2_now == HIGH))
                SpanDown = Last;
        }
        else
        {
            if ((B2_Last == HIGH) && (B2_now == LOW))
                SpanDown = Last;
            else if ((B2_Last == LOW) && (B2_now == HIGH))
                SpanDown = Next;
            else if ((B2_Last == B2_now) && (B2_now == LOW))
                SpanDown = Last;
            else if ((B2_Last == B2_now) && (B2_now == HIGH))
                SpanDown = Next;
        }
        B1_Last = B1_now;
        B2_Last = B2_now;
    }
    else if (BA_now == LOW)
    {
        while (BA_now != HIGH)
        {
            vTaskDelay(200 / portTICK_RATE_MS);
            BA_now = digitalRead(BA);
        }
        SpanDown = Down;
    }
}

KeyDown Key::GetSpan()
{
    return SpanDown;
}

KeyDown Key::GetKey()
{
    return NowKeyDown;
}

void Key::KeyClear()
{
    NowKeyDown = NullKey;
    SpanDown = NullKey;
}