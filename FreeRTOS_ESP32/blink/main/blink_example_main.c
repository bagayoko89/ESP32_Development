/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN 33
int i=0;

void TAskA(void *pvParameters1){
    while(1){
        printf("Task running on Core %d\n",xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void TAskB(void *pvParameters2){
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    while(1){
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void TAskC(void *pvParameters3){
    while(1){
        printf("(count=%d)\n",i);
        vTaskDelay(pdMS_TO_TICKS(1000));
        i++;
    }
}


void app_main(void)
{
    xTaskCreate(TAskA, "TAskA",2048,NULL,5,NULL);
    xTaskCreatePinnedToCore(TAskB, "TAskB",2048,NULL,5,NULL,0);
    xTaskCreatePinnedToCore(TAskC, "TAskC",2048,NULL,5,NULL,1);
}
