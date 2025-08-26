#include "esp_timer.h"
#define buzzer_pin 32
#define led_pin 33
esp_timer_handle_t my_timer;
static bool buzzerState = false;
void toggleBuzzer(){
  buzzerState = !buzzerState;
  digitalWrite(buzzer_pin, buzzerState);
}
void toggleLED(){
  if(buzzerState){
    digitalWrite(led_pin, HIGH);
  }
  else digitalWrite(led_pin, LOW);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buzzer_pin,OUTPUT);
  pinMode(led_pin,OUTPUT);

  const esp_timer_create_args_t timer_args = {
    .callback = &toggleBuzzer,   
    .arg = NULL,              
    .dispatch_method = ESP_TIMER_TASK,
    .name = "my_timer"       
  };

  // Création du timer
  esp_timer_create(&timer_args, &my_timer);

  esp_timer_start_periodic(my_timer, 2*500000);

}

void loop() {
  toggleLED();
}
