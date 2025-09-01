#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN 33

void task_delay(void *pvParameters){
    while(1){
        printf("vTaskDelay: %lu ms\n", (unsigned long)(xTaskGetTickCount()* portTICK_PERIOD_MS));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task_delay_until(void *pvParameters3){
    TickType_t last_wake= xTaskGetTickCount();
    while(1){
        printf("vTaskDelayUntil: %lu ms\n", (unsigned long)(xTaskGetTickCount()* portTICK_PERIOD_MS));
        vTaskDelayUntil(&last_wake,pdMS_TO_TICKS(1000));
    }
}


void app_main(void)
{
    xTaskCreate(task_delay, "TaskDelay",2048,NULL,5,NULL);
    xTaskCreate(task_delay_until, "TaskDelayUntil",2048,NULL,5,NULL);
}
