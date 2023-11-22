//
// Created by 22755 on 2023/11/15.
//
#include "lvgl.h"

void Animotion(lv_anim_t ani,lv_obj_t *parant,lv_anim_exec_xcb_t exec_cb,lv_anim_path_cb_t path_cb,uint32_t time,uint32_t delay,lv_anim_ready_cb_t ready_cb,int32_t start,int32_t end)
{
    lv_anim_init(&ani);
    lv_anim_set_var(&ani,parant);
    lv_anim_set_exec_cb(&ani,exec_cb);
    lv_anim_set_values(&ani,start,end);
    lv_anim_set_time(&ani,time);
    lv_anim_set_delay(&ani,delay);
    lv_anim_set_path_cb(&ani,path_cb);
    lv_anim_set_ready_cb(&ani,ready_cb);
    lv_anim_start(&ani);
}
void create_obj(lv_obj_t* obj,lv_obj_t * parent,uint32_t Width,uint32_t Height)
{
    obj = lv_obj_create(parent);
    lv_obj_set_size(obj,Width,Height);
}
lv_anim_t menu_change;
void Menu_Load(lv_obj_t *obj,lv_scr_load_anim_t anim_type,uint32_t time,uint32_t delay)
{

    lv_disp_t * d = lv_obj_get_disp(obj);
    lv_anim_set_var(&menu_change,obj);
    switch (anim_type) {
        case LV_SCR_LOAD_ANIM_MOVE_LEFT:
            lv_anim_set_exec_cb(&menu_change, (lv_anim_exec_xcb_t)lv_obj_set_x);
            lv_anim_set_values(&menu_change, lv_disp_get_hor_res(d), 0);
            break;
        case LV_SCR_LOAD_ANIM_MOVE_RIGHT:
            lv_anim_set_exec_cb(&menu_change, (lv_anim_exec_xcb_t)lv_obj_set_x);
            lv_anim_set_values(&menu_change, -lv_disp_get_hor_res(d), 0);
            break;
        case LV_SCR_LOAD_ANIM_MOVE_TOP:
            lv_anim_set_exec_cb(&menu_change, (lv_anim_exec_xcb_t)lv_obj_set_y);
            lv_anim_set_values(&menu_change, lv_disp_get_ver_res(d), 0);
            break;
        case LV_SCR_LOAD_ANIM_MOVE_BOTTOM:
            lv_anim_set_exec_cb(&menu_change, (lv_anim_exec_xcb_t)lv_obj_set_y);
            lv_anim_set_values(&menu_change, -lv_disp_get_ver_res(d), 0);
            break;
    }
//    lv_anim_set_exec_cb(&menu_ani,(lv_anim_exec_xcb_t) lv_obj_set_y);
//    lv_anim_set_values(&menu_ani,240,0);
    lv_anim_set_time(&menu_change,time);
    lv_anim_set_delay(&menu_change,delay);
    lv_anim_set_path_cb(&menu_change,lv_anim_path_ease_out);
    lv_anim_start(&menu_change);
}