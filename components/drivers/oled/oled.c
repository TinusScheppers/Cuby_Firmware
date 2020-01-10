#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>
#include <u8g2.h>

#include "sdkconfig.h"
#include "u8g2_esp32_hal.h"

// SDA - GPIO21
#define PIN_SDA 23

// SCL - GPIO22
#define PIN_SCL 22

// Reset
#define PIN_RST 21

static const char *TAG = "ssd1306";

u8g2_t oled_init()
{
	u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
	u8g2_esp32_hal.sda = PIN_SDA;
	u8g2_esp32_hal.scl = PIN_SCL;
	u8g2_esp32_hal.reset = PIN_RST;
	u8g2_esp32_hal_init(u8g2_esp32_hal);

	u8g2_t u8g2; // a structure which will contain all the data for one display
	u8g2_Setup_ssd1306_i2c_128x32_univision_f(
		&u8g2,
		U8G2_R0,
		//u8x8_byte_sw_i2c,
		u8g2_esp32_i2c_byte_cb,
		u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure
	u8x8_SetI2CAddress(&u8g2.u8x8, 0x78);

	ESP_LOGI(TAG, "u8g2_InitDisplay");
	u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,

	ESP_LOGI(TAG, "u8g2_SetPowerSave");
	u8g2_SetPowerSave(&u8g2, 0); // wake up display
	ESP_LOGI(TAG, "u8g2_ClearBuffer");
	u8g2_ClearBuffer(&u8g2);

	return u8g2;
}

void oled_drawString(u8g2_t u8g2, char *string)
{
	// gpio_pad_select_gpio(BLINK_GPIO);
	// /* Set the GPIO as a push/pull output */
	// gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
	// gpio_set_level(BLINK_GPIO, 1);

	// ESP_LOGI(TAG, "u8g2_DrawBox");
	// u8g2_DrawBox(&u8g2, 0, 26, 80, 6);
	// u8g2_DrawFrame(&u8g2, 0, 26, 100, 6);
	u8g2_ClearDisplay(&u8g2);
	ESP_LOGI(TAG, "u8g2_SetFont");
	u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
	ESP_LOGI(TAG, "u8g2_DrawStr");
	u8g2_DrawStr(&u8g2, 2, 17, "test");
	ESP_LOGI(TAG, "u8g2_SendBuffer");
	u8g2_SendBuffer(&u8g2);

	ESP_LOGI(TAG, "All done!");

	// vTaskDelete(NULL);
}

// void app_main()
// {
// 	xTaskCreate(task_test_SSD1306i2c, "task_test_SSD1306i2c", 2 * 4096, NULL, 10, NULL);
// 	// task_test_SSD1306i2c();
// }
