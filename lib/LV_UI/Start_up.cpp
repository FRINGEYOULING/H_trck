//
// Created by 22755 on 2023/11/15.
//

#include "Start_up.h"
#include "lvgl.h"
#include <animotion.h>
#include "Diplat.h"
#include "Statue_Bar.h"
LV_IMG_DECLARE(yuanshen);
LV_FONT_DECLARE(font_bahnschrift_17);
lv_obj_t *yush;
lv_obj_t *Start_over;
static void yuanshen_cb(lv_anim_t * anim)
{
    lv_obj_del(yush);
    Start_UP();
    Menu_Load(Start_over,LV_SCR_LOAD_ANIM_MOVE_TOP,650,50);
    /* 动画结束时执行的操作 */
}

static void Start_end_cb(lv_anim_t * anim)
{
    lv_obj_del(Start_over);
    Diplat();
    Statue_Bar_Cre();
    Ticke_init();
    Menu_Load(main_home,LV_SCR_LOAD_ANIM_MOVE_BOTTOM,750,50);
    /* 动画结束时执行的操作 */
}

void yuanshen_qd()
{
    lv_obj_t *yuan_img;
    lv_anim_t ys_ani;
    lv_anim_init(&ys_ani);
    yush = lv_obj_create(lv_scr_act());
    lv_obj_set_size(yush,240,240);
    lv_obj_set_style_radius(yush,0,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(yush,lv_color_hex(0xFFFFFF),LV_STATE_DEFAULT);

    lv_obj_t *yuan = lv_obj_create(yush);
    lv_obj_set_size(yuan,150,100);
    lv_obj_center(yuan);
    lv_obj_set_style_border_width(yuan,0,LV_STATE_DEFAULT);
    yuan_img = lv_img_create(yuan);
    lv_img_set_src(yuan_img,&yuanshen);
    lv_obj_center(yuan_img);
    lv_anim_set_var(&ys_ani,yuan);
    lv_anim_set_exec_cb(&ys_ani,(lv_anim_exec_xcb_t) lv_obj_set_height);
    lv_obj_set_scrollbar_mode(yuan,LV_SCROLLBAR_MODE_OFF );
    lv_anim_set_time(&ys_ani,3500);
    lv_anim_set_values(&ys_ani,0,150);
    lv_anim_set_delay(&ys_ani,1000);
    lv_anim_set_path_cb(&ys_ani,lv_anim_path_ease_out);
    lv_anim_set_ready_cb(&ys_ani,yuanshen_cb);
    lv_anim_start(&ys_ani);
}


void Start_UP()
{
    lv_anim_t start_up;
    lv_anim_t start_up_lable;
    lv_anim_init(&start_up);
    lv_anim_init(&start_up_lable);
    Start_over = lv_obj_create(lv_scr_act());
    lv_obj_set_size(Start_over,240,240);
    lv_obj_set_style_bg_color(Start_over,lv_color_hex(0x000000),LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(Start_over,0,LV_STATE_DEFAULT);

    lv_obj_t* cont = lv_obj_create(Start_over);
    lv_obj_remove_style_all(cont);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(cont, 110, 50);
    lv_obj_set_style_border_color(cont, lv_color_hex(0xff931e), 0);
    lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_border_width(cont, 3, 0);
    lv_obj_set_style_border_post(cont, true, 0);
    lv_obj_center(cont);
    lv_anim_set_var(&start_up,cont);
    lv_anim_set_exec_cb(&start_up,(lv_anim_exec_xcb_t) lv_obj_set_width);
    lv_anim_set_time(&start_up,2000);
    lv_anim_set_values(&start_up,0,110);
    lv_anim_set_delay(&start_up,400);
    lv_anim_set_ready_cb(&start_up,Start_end_cb);
    lv_anim_set_path_cb(&start_up,lv_anim_path_ease_out);
    lv_anim_start(&start_up);

    lv_obj_t* label = lv_label_create(Start_over);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_22, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text(label, "H-TARCK");
    lv_obj_set_style_text_font(label,&font_bahnschrift_17, 0);
    lv_obj_center(label);
    lv_anim_set_var(&start_up_lable,label);
    lv_anim_set_exec_cb(&start_up_lable,(lv_anim_exec_xcb_t) lv_obj_set_height);
    lv_anim_set_time(&start_up_lable,600);
    lv_anim_set_values(&start_up_lable,0,25);
    lv_anim_set_delay(&start_up_lable,800);
    lv_anim_set_path_cb(&start_up_lable,lv_anim_path_ease_out);
    lv_anim_start(&start_up_lable);
}