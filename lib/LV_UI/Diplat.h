//
// Created by 22755 on 2023/11/15.
//

#ifndef LVGL_DIPLAT_H
#define LVGL_DIPLAT_H
#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl.h"

typedef struct
{
    float lnt;
    float lat;
    float l_lnt;
    float l_lat;
    float d_lnt;
    float d_lat;
    float distance;
}location;

typedef struct
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
}Sport_Time;
extern float Trip;
extern uint8_t Sport_Statue;
extern uint8_t Menu_state;
extern lv_obj_t *main_home;
lv_obj_t* Btn_Create(lv_obj_t* par, const void* img_src, lv_coord_t x_ofs);
void Diplat();
void SubInfoGrp_Create(lv_obj_t* par, const char* unitText);
void Sport_Handle();
void Style_Num_Init();
void Ticke_init();
#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif //LVGL_DIPLAT_H
