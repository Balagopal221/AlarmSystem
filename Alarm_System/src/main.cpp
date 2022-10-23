// COMP-10184 – Mohawk College
// PIR Sensor Test Application
// Turn on the blue LED with motion is detected.

#include <Arduino.h>

// digital input pin definitions
#define PIN_PIR D5
#define PIN_BUTTON D6

int lightState = 0;
unsigned long lastTimeMotionDetected = millis();
unsigned long debounceDuration = 50;

// *************************************************************
void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // configure the LED output
  pinMode(LED_BUILTIN, OUTPUT);

  // PIR sensor is an INPUT
  pinMode(PIN_PIR, INPUT);

  // Button is an INPUT
  pinMode(PIN_BUTTON, INPUT_PULLUP);
}

// *************************************************************
void loop()
{
  bool bPIR;
  unsigned long currentMillis = millis();
  // read PIR sensor (true = Motion detected!).  As long as there
  // is motion, this signal will be true.  About 2.5 seconds after
  // motion stops, the PIR signal will become false.
  bPIR = digitalRead(PIN_PIR);

  if (bPIR)
  {
    if (millis() - lastTimeMotionDetected >= debounceDuration)
    {
      lastTimeMotionDetected = millis();
      while (lastTimeMotionDetected - millis() < 10000)
      {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(2500);
        digitalWrite(LED_BUILTIN, LOW);
      }
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}