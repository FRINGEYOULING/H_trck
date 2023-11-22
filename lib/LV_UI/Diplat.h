//
// Created by 22755 on 2023/11/15.
//

#ifndef LVGL_DIPLAT_H
#define LVGL_DIPLAT_H
#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl.h"

extern uint8_t Menu_state;
extern lv_obj_t *main_home;
lv_obj_t* Btn_Create(lv_obj_t* par, const void* img_src, lv_coord_t x_ofs);
void Diplat();
void SubInfoGrp_Create(lv_obj_t* par, const char* unitText);
#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif //LVGL_DIPLAT_H
