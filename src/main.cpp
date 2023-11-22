#include <Arduino.h>
#include <HAL.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <SD.h>
#include "Start_up.h"
// put function declarations here:
void setup() {
  // put your setup code here, to run once:
  HAL::HAL_Init();
  yuanshen_qd();
  Serial.printf("Deafult free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
  Serial.printf("PSRAM free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
  Serial.printf("Flash size: %d bytes\n", ESP.getFlashChipSize());

}

void loop() {
  // put your main code here, to run repeatedly:
  lv_task_handler();
  delay(5);
}