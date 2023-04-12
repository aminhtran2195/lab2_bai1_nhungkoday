/* i2c - Example

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   See README.md file to get detailed usage of this example.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "ssd1306.h"

//static const char *TAG = "i2c-example";

#define OLED_SCL GPIO_NUM_22             
#define OLED_SDA GPIO_NUM_21          
#define I2C_MASTER_FREQ_HZ CONFIG_I2C_MASTER_FREQUENCY        /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */

const char* Minhstr = "\n   20521616\n\nTran Anh Minh";
const char* Huestr = "\n   20521619\n\nVan Nhat Minh";
const char* Namstr = "\n   20521630\n\nNguyen Huu Nam";

TaskHandle_t hdltask1 = NULL;

/**
 * @brief i2c master initialization
 */
static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_NUM_0;
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = OLED_SDA,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = OLED_SCL,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
        // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
    };
    esp_err_t err = i2c_param_config(i2c_master_port, &conf);
    if (err != ESP_OK) {
        return err;
    }
    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

static void DisplayOled_Task(void* agr){
    ssd1306_init();
    while(1){
        task_ssd1306_display_clear(NULL);  
        task_ssd1306_display_text(Minhstr);
        vTaskDelay(2000/portTICK_RATE_MS);

        task_ssd1306_display_clear(NULL);
        task_ssd1306_display_text(Huestr);
        vTaskDelay(2000/portTICK_RATE_MS);

        task_ssd1306_display_clear(NULL);
        task_ssd1306_display_text(Namstr);
         vTaskDelay(2000/portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    ESP_ERROR_CHECK(i2c_master_init());
    xTaskCreate(DisplayOled_Task, "DisplayOled_task1", 1024 * 2, (void *)0, tskIDLE_PRIORITY,hdltask1);
}

