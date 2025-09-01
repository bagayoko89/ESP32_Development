#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN 33

void task_low(void *pvParameters){
    while(1){
        printf("Low priority task running on core %d\n",xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task_medium(void *pvParameters3){
    while(1){
        printf("Medium priority task running on core %d\n",xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void task_high(void *pvParameters3){
    int i=0;
    while(1){
        printf("High priority task running on core %d and count=%d\n",xPortGetCoreID(), i);
        vTaskDelay(pdMS_TO_TICKS(1000));
        if(i>=4){
            printf("Priority changed\n");
            vTaskPrioritySet(NULL, 2);
            i=0;
        }
        i++;
    }
}


void app_main(void)
{
    xTaskCreate(task_low, "LowPriority",2048,NULL,3,NULL);
    xTaskCreate(task_medium, "MediumPriority",2048,NULL,5,NULL);
    xTaskCreate(task_high, "HighPriority",2048,NULL,8,NULL);
}
