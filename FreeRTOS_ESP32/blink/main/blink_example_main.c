/**
 * @file blink_two_leds.c
 * @brief ESP-IDF FreeRTOS demo comparing vTaskDelay (relative) vs vTaskDelayUntil (absolute).
 *
 * This example blinks two LEDs at different rates to illustrate timing drift
 * with vTaskDelay() and the stable cadence of vTaskDelayUntil(). It also
 * includes a status task that periodically prints uptime for reference.
 *
 * Wiring:
 *   - LED1 (GPIO2 by default) -> resistor -> GND
 *   - LED2 (GPIO4 by default) -> resistor -> GND
 *
 * Notes:
 *   - Adjust LED1_GPIO / LED2_GPIO to match your hardware.
 *   - Console output includes timestamps to visualize drift behavior.
 */

#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_log.h"
#define TAG "DAY11"
#define MAX_RESSOURCES 3

SemaphoreHandle_t ressource_sem;


void worker_task(void *pvParameters){
    int id = (int) pvParameters;

    while(1){
        if(xSemaphoreTake(ressource_sem, portMAX_DELAY)){
            printf("Task %d acquired resource\n", id);
            vTaskDelay(pdMS_TO_TICKS(2000));
            printf("Task %d releasing resource\n", id);
            xSemaphoreGive(ressource_sem);

        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void){
    ressource_sem=xSemaphoreCreateCounting(MAX_RESSOURCES, MAX_RESSOURCES);
    if(ressource_sem==NULL){
        printf("Failed to create counting semaphore\n");
        return;
    }

    for(int i=1; i<5;i++){
        char task_name[16];
        sprintf(task_name, "Worker%d", i);
        xTaskCreate(worker_task, task_name, 2048, (void *)i, 5, NULL);
    }
}