#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/list.h"
#include <freertos/semphr.h>
TimerHandle_t blink_timer;
#define buzzer_pin 32
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buzzer_pin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(buzzer_pin,HIGH);
  delay(3000);
  digitalWrite(buzzer_pin,LOW);
  delay(2000);

}
