/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void hello_task(void *pvParameters){
    while(1){
        printf("Hello from freeRTOS\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void app_main(void)
{
    xTaskCreate(hello_task, "HelloTask",2048,NULL,5,NULL);

}
