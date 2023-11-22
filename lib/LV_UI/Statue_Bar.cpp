#include "lvgl.h"
#include "Statue_Bar.h"
#include "animotion.h"
#include "TinyGPS++.h"
lv_obj_t *Statue_Bar;
lv_obj_t *Satellite_num;
lv_obj_t *time_lable;
lv_obj_t *img_src;
lv_timer_t *RTC_timer;
lv_obj_t *s_statue;
LV_IMG_DECLARE(img_src_satellite);
extern char clock_buff[64];
extern TinyGPSPlus gps;;
void Img_UPDATE(lv_timer_t *tmr)
{
    lv_label_set_text_fmt(time_lable,"%s",clock_buff);
    lv_label_set_text_fmt(Satellite_num,"%d",gps.satellites.value());
}

void Statue_Bar_Cre()
{
    lv_anim_t appear;
    lv_anim_init(&appear);
    Statue_Bar = lv_obj_create(lv_layer_top());
    lv_obj_set_size(Statue_Bar,240,15);
    lv_obj_align(Statue_Bar,LV_ALIGN_TOP_MID,0,0);
    lv_obj_set_style_radius(Statue_Bar,0,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(Statue_Bar,lv_color_hex(0x333333),LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(Statue_Bar,0,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(Statue_Bar,LV_OPA_0,LV_STATE_DEFAULT);
    lv_obj_clear_flag(Statue_Bar, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(lv_layer_top(), LV_STATE_DEFAULT);
    img_src = lv_img_create(Statue_Bar);
    lv_img_set_src(img_src,&img_src_satellite);
    lv_obj_align(img_src,LV_ALIGN_RIGHT_MID,-15,0);
    time_lable = lv_label_create(Statue_Bar);
    lv_obj_set_align(time_lable,LV_ALIGN_LEFT_MID);
    lv_label_set_text_fmt(time_lable,"%02d:%02d",0,0);
    lv_obj_set_style_text_color(time_lable,lv_color_white(),LV_STATE_DEFAULT);
    Satellite_num = lv_label_create(Statue_Bar);
    lv_obj_set_align(Satellite_num,LV_ALIGN_RIGHT_MID);
    lv_label_set_text_fmt(Satellite_num,"%d",0);
    lv_obj_set_style_text_color(Satellite_num,lv_color_white(),LV_STATE_DEFAULT);
    s_statue = lv_label_create(Statue_Bar);
    lv_obj_set_align(s_statue,LV_ALIGN_CENTER);
    lv_label_set_text_fmt(s_statue,"   ");
    lv_obj_set_style_text_color(s_statue,lv_color_white(),LV_STATE_DEFAULT);
    lv_anim_set_var(&appear,Statue_Bar);
    lv_anim_set_exec_cb(&appear, (lv_anim_exec_xcb_t)lv_obj_set_height);
    lv_anim_set_time(&appear, 500);
    lv_anim_set_values(&appear, 0, 15);
    lv_anim_set_delay(&appear, 600);
    lv_anim_set_path_cb(&appear, lv_anim_path_ease_out);
    lv_anim_start(&appear);
    RTC_timer = lv_timer_create(Img_UPDATE,100,0);
    lv_timer_set_repeat_count(RTC_timer,-1);
}


