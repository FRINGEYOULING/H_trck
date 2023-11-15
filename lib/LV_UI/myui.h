//
// Created by 22755 on 2023/11/9.
//

#ifndef LVGL_MYUI_H
#define LVGL_MYUI_H

#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl.h"
void my_ui();
void data_update(lv_timer_t * tmr);
void menu_ob();
void lv_all_init();
void Menu_load(lv_obj_t *obj,lv_obj_t *old_obj,lv_scr_load_anim_t anim_type,uint32_t time,uint32_t delay);
void Time_reset(uint32_t period,int32_t repeat_count);
void Start_up();
void yuanshen_qidong();

#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif //LVGL_MYUI_H
