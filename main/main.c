#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// Include the headers of your components
// เพื่อให้สามารถเรียกใช้ฟังก์ชันจาก components ได้
#include "sensor.h"
#include "display.h"
#include "led.h"

// กำหนด TAG สำหรับการแสดง Log
static const char* TAG = "MAIN_APP";

void app_main(void) {
    ESP_LOGI(TAG, "Starting application...");
    
    // Initialize the components
    // เรียกใช้ฟังก์ชัน initialization ของแต่ละ component
    sensor_init();
    display_init();
    led_init();

    // Main application loop
    // วนลูปการทำงานหลักของโปรแกรม
    while (1) {
        // Read data from the sensor
        float temperature = sensor_read_temperature();
        
        // Prepare message to display
        char message[50];
        sprintf(message, "Temp: %.2f C", temperature);
        
        // Display message on screen
        display_show_message(message);

        // Control the LED based on the temperature
        if (temperature > 30.0) {
            led_turn_on();
        } else {
            led_turn_off();
        }

        // Wait for 5 seconds before repeating the loop
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}