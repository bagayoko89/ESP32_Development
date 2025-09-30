/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#define WIFI_CONNECTED_BIT BIT0
#define MQTT_CONNECTED_BIT BIT1

static EventGroupHandle_t app_event_group;
static const char *TAG = "EVENT_EX1";

// Simulated wifi connection 

void wifi_task(void *pvparameters){
    vTaskDelay(pdMS_TO_TICKS(2000));
    printf("Wi_Fi Connected");
    xEventGroupSetBits(app_event_group, WIFI_CONNECTED_BIT);
    vTaskDelete(NULL);
}

void mqtt_task(void *pvparameters){
    vTaskDelay(pdMS_TO_TICKS(4000));
    printf("MQTT Connected");
    xEventGroupSetBits(app_event_group, MQTT_CONNECTED_BIT);
    vTaskDelete(NULL);
}

void controller_task(void *pvparameters){
    printf("Waiting for MQTT+WiFi...");
    xEventGroupWaitBits(app_event_group, WIFI_CONNECTED_BIT | MQTT_CONNECTED_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
    ESP_LOGI(TAG, "Controller: Running...");
    vTaskDelay(pdMS_TO_TICKS(2000));
}

void app_main(void){
    app_event_group = xEventGroupCreate();
    xTaskCreate(wifi_task, "wifi_task", 2048, NULL, 2, NULL);
    xTaskCreate(mqtt_task, "mqtt_task", 2048, NULL, 2, NULL);
    xTaskCreate(controller_task, "controller_task", 2048, NULL, 2, NULL);
}
