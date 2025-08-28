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
TaskHandle_t task_handle_blink = NULL;

void blink_task(void *pvParameters){
    int i=0;
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    while(1){
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
        printf("count=%d\n",i);
        i++;
        if(i>=10){
            printf("Task deleting itself...\n");
            vTaskDelete(NULL);
        }
    }
}

void control_task(void *pvParameters3){
    printf("control task running ...\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    if(task_handle_blink!=NULL){
        printf("control task deleting blink Task ...\n");
        vTaskDelete(task_handle_blink);
    }
    vTaskDelete(NULL);
}


void app_main(void)
{
    xTaskCreate(blink_task, "Blink_task",2048,NULL,5,&task_handle_blink);
    xTaskCreate(control_task, "Control_task",2048,NULL,5,NULL);
}
