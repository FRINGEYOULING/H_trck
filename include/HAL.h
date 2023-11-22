#ifndef __HAL_H
#define __HAL_H

#include <Arduino.h>
#include "HAL.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl.h"

namespace HAL
{
    void HAL_Init(void);
    void GPS_Update(void);
    void Time_init(void);
    void Encoder_Init(void);
    int32_t Encoder_GetDiff(void);
}
#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif 
