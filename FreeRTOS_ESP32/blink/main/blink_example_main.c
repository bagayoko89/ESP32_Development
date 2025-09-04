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
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#define QUEUE_LENGTH 5
QueueHandle_t queue;


void producer_task(void *pv){
    int count=1;
    while(1){
        if(xQueueSend(queue, &count, pdMS_TO_TICKS(100))==pdPASS){
            printf("Producer sent: %d\n", count);
            count++;
        } else {
            printf("Producer: Queue full!\n");
            vTaskSuspend(NULL);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void consumer_task(void *pv){
    int value;
    while(1){
        if(xQueueReceive(queue,&value, pdMS_TO_TICKS(1000))==pdPASS){
            printf("Consumer received: %d\n",value);
        } else {
            printf("Consumer: Queue empty!\n");
        }
        if(value%2==0){
            printf("The number is even\n");
        }
        else printf("The number is odd\n");
    }
}

void app_main(void){
    queue=xQueueCreate(QUEUE_LENGTH, sizeof(int));
    if(queue==NULL){
        printf("Failed to create queue\n");
        return;
    }
    xTaskCreate(producer_task, "Producer", 2048, NULL, 5, NULL);
    xTaskCreate(consumer_task, "Consumer", 2048, NULL, 5, NULL);
}