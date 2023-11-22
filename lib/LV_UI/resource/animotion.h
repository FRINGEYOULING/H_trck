//
// Created by 22755 on 2023/11/15.
//

#ifndef LVGL_ANIMOTION_H
#define LVGL_ANIMOTION_H
#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl/lvgl.h"
void Animotion(lv_anim_t ani,lv_obj_t *parant,lv_anim_exec_xcb_t exec_cb,lv_anim_path_cb_t path_cb,
               uint32_t time,uint32_t delay,lv_anim_ready_cb_t ready_cb,int32_t start,int32_t end);

void create_obj(lv_obj_t* obj,lv_obj_t * parent,uint32_t Width,uint32_t Height);

void Menu_Load(lv_obj_t *obj,lv_scr_load_anim_t anim_type,uint32_t time,uint32_t delay);
#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif //LVGL_ANIMOTION_H
