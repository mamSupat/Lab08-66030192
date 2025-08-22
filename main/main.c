#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sensor.h"
#include "display.h"
#include "led.h"

static const char *TAG = "LAB7-3";

void app_main(void)
{
    ESP_LOGI(TAG, "🚀 Lab 7-3: Custom Components Demo (sensor + display + led) Started");
    ESP_LOGI(TAG, "📦 Using components created with idf.py create-component");

    // เริ่มต้น components
    sensor_init();
    display_init();
    led_init();

    int reading_count = 0;

    while (1)
    {
        reading_count++;
        ESP_LOGI(TAG, "📋 Reading #%d", reading_count);

        display_clear();

        // อ่านข้อมูลจาก sensor component
        float temp = sensor_read_temperature();
        float hum = sensor_read_humidity();

        // คำนวณ Heat Index
        float heat_index = temp + 0.5 * hum;
        ESP_LOGI(TAG, "🔥 Heat Index: %.2f", heat_index);

        // แสดงข้อมูลผ่าน display component
        display_show_sensor_data(temp, hum, heat_index);

        // แสดงสถานะ + ควบคุม LED ตามค่า Heat Index
        if (heat_index < 80)
        {
            display_show_status("✅ Comfortable");
            led_off();
        }
        else if (heat_index < 90)
        {
            display_show_status("⚠️  Caution");
            led_toggle();   // กระพริบๆ แบบสุ่มตามรอบ loop
        }
        else
        {
            display_show_status("🚨 Warning");
            led_on();       // เปิดไฟ LED ค้างเตือน
        }

        ESP_LOGI(TAG, "==========================================");
        vTaskDelay(pdMS_TO_TICKS(6000));
    }
}