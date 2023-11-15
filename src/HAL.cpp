#include <Arduino.h>
#include <HAL.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
void HAL::HAL_Init(void)
{
    Serial.begin(115200);
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
}