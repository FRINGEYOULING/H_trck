//
// Created by 22755 on 2023/11/15.
//

#include <Diplat.h>
#include "lvgl.h"
#include <animotion.h>
#include "SysIfo.h"
LV_FONT_DECLARE(font_bahnschrift_65);
LV_FONT_DECLARE(font_bahnschrift_17);
LV_FONT_DECLARE(font_bahnschrift_13);
LV_IMG_DECLARE(img_src_menu);
LV_IMG_DECLARE(img_src_locate);
LV_IMG_DECLARE(img_src_pause);
LV_IMG_DECLARE(img_src_start);
#define Sysinfo 1
#define map_loca 2
lv_obj_t *main_home;
uint8_t Menu_state = 0;
typedef struct {
    lv_obj_t* menu;
    lv_obj_t *start;
    lv_obj_t *locat;
}Button_num;
Button_num button;
lv_group_t *btn_group;
static void Btn_event(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    if(obj == button.menu)
    {
        lv_obj_del(main_home);
        Create();
        Menu_Load(lv_scr_act(),LV_SCR_LOAD_ANIM_MOVE_LEFT,750,50);
        Menu_state = Sysinfo;
    }
//    else if(obj == button.start)
//    {
//        lv_obj_del(main_home);
//        yuanshen_qd();
//    }
//    else if(obj == button.locat)
//    {
//        lv_scr_load_anim_t anim_type = LV_SCR_LOAD_ANIM_MOVE_RIGHT;
//        Menu_Load(main_home,anim_type,750,50);
//    }
}



void Diplat()
{
    main_home = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(main_home);
    lv_obj_set_size(main_home,240,240);
    lv_obj_set_scrollbar_mode(main_home,LV_SCROLLBAR_MODE_OFF );
//    lv_obj_clear_flag(main_home, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(main_home,lv_color_hex(0x000000),LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(main_home,0,LV_STATE_DEFAULT);

    lv_anim_t ani_foce;
    lv_anim_init(&ani_foce);
    lv_obj_t *main_force = lv_obj_create(main_home);
    lv_obj_set_align(main_force,LV_ALIGN_TOP_MID);
    lv_obj_set_size(main_force,240,0);
    lv_obj_set_style_border_width(main_force,0,LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(main_force,LV_SCROLLBAR_MODE_OFF );
    lv_obj_set_style_bg_color(main_force,lv_color_hex(0x363636),LV_STATE_DEFAULT);
    lv_obj_set_style_radius(main_force,15,LV_STATE_DEFAULT);
    lv_obj_set_y(main_force, -36);
    lv_anim_set_var(&ani_foce,main_force);
    lv_anim_set_exec_cb(&ani_foce,(lv_anim_exec_xcb_t) lv_obj_set_height);
    lv_anim_set_time(&ani_foce,750);
    lv_anim_set_values(&ani_foce,0,131);
    lv_anim_set_delay(&ani_foce,400);
    lv_anim_set_path_cb(&ani_foce,lv_anim_path_ease_out);
    lv_anim_start(&ani_foce);

    lv_obj_t *home_lable = lv_label_create(main_force);
    lv_label_set_text_fmt(home_lable,"00");
    lv_obj_set_style_text_color(home_lable,lv_color_hex(0xFFFFFF),LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(home_lable,&font_bahnschrift_65,LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_align(home_lable,LV_ALIGN_CENTER,0,12);

    home_lable = lv_label_create(main_force);
    lv_label_set_text_fmt(home_lable,"km/h");
    lv_obj_set_style_text_color(home_lable,lv_color_hex(0xFFFFFF),LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(home_lable,&font_bahnschrift_17,LV_STATE_DEFAULT);
    lv_obj_align(home_lable,LV_ALIGN_BOTTOM_MID,0,8);

    lv_anim_t ani_mation;
    lv_anim_init(&ani_mation);
    lv_obj_t* mation = lv_obj_create(main_home);
    lv_obj_remove_style_all(mation);
    lv_obj_set_style_bg_color(mation, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_size(mation, LV_HOR_RES, 90);
    lv_obj_align(mation, LV_ALIGN_TOP_MID, 0, 92);
    lv_obj_set_flex_flow(mation, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(
            mation,
            LV_FLEX_ALIGN_SPACE_EVENLY,
            LV_FLEX_ALIGN_CENTER,
            LV_FLEX_ALIGN_CENTER
    );
    lv_obj_set_style_border_width(mation, 0, LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(mation,LV_SCROLLBAR_MODE_OFF );
    lv_anim_set_var(&ani_mation, mation);
    lv_anim_set_exec_cb(&ani_mation,(lv_anim_exec_xcb_t) lv_obj_set_height);
    lv_anim_set_time(&ani_mation,700);
    lv_anim_set_values(&ani_mation,0,90);
    lv_anim_set_delay(&ani_mation,600);
    lv_anim_set_path_cb(&ani_mation,lv_anim_path_ease_in);
    lv_anim_start(&ani_mation);

    const char* unitText[4] =
    {
            "AVG",
            "Time",
            "Trip",
            "Calorie"
    };
    for(int i=0;i<4;i++)
    {
        SubInfoGrp_Create(mation,unitText[i]);
    }

    lv_anim_t btn_anim;
    lv_anim_init(&btn_anim);
    lv_obj_t* btn_cont = lv_obj_create(main_home);
    lv_obj_remove_style_all(btn_cont);
    lv_obj_set_size(btn_cont, LV_HOR_RES, 40);
    lv_obj_align(btn_cont,LV_ALIGN_BOTTOM_MID,0,0);
    lv_anim_set_var(&btn_anim, btn_cont);
    lv_anim_set_exec_cb(&btn_anim, (lv_anim_exec_xcb_t)lv_obj_set_height);
    lv_anim_set_time(&btn_anim,600);
    lv_anim_set_values(&btn_anim,0,40);
    lv_anim_set_delay(&btn_anim,700);
    lv_anim_set_path_cb(&btn_anim,lv_anim_path_ease_out);
    lv_anim_start(&btn_anim);
    button.menu = Btn_Create(btn_cont,&img_src_menu, 70);
    button.start = Btn_Create(btn_cont,&img_src_start, 0);
    button.locat = Btn_Create(btn_cont,&img_src_locate, -70);
    btn_group = lv_group_get_default();
    lv_group_add_obj(btn_group,button.start);
    lv_group_add_obj(btn_group,button.menu);
    lv_group_add_obj(btn_group,button.locat);
    lv_obj_add_event_cb(button.menu,Btn_event,LV_EVENT_CLICKED,NULL);
    lv_obj_add_event_cb(button.start,Btn_event,LV_EVENT_CLICKED,NULL);
    lv_obj_add_event_cb(button.locat,Btn_event,LV_EVENT_CLICKED,NULL);
}



void SubInfoGrp_Create(lv_obj_t* par, const char* unitText)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 93, 39);

    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
            cont,
            LV_FLEX_ALIGN_SPACE_AROUND,
            LV_FLEX_ALIGN_CENTER,
            LV_FLEX_ALIGN_CENTER
    );

    lv_obj_t* label = lv_label_create(cont);
    lv_obj_set_style_text_font(label,&font_bahnschrift_17, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);

    label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, &font_bahnschrift_13, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xb3b3b3), 0);
    lv_label_set_text(label, unitText);
}

lv_obj_t* Btn_Create(lv_obj_t* par, const void* img_src, lv_coord_t x_ofs)
{
    lv_obj_t* obj = lv_obj_create(par);
    lv_obj_remove_style_all(obj);
    lv_obj_set_size(obj, 40, 31);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_align(obj, LV_ALIGN_CENTER, x_ofs, 0);
    lv_obj_set_style_bg_img_src(obj, img_src, 0);

    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
    lv_obj_set_style_width(obj, 45, LV_STATE_PRESSED);
    lv_obj_set_style_height(obj, 25, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x666666), 0);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xbbbbbb), LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff931e), LV_STATE_FOCUSED);
    lv_obj_set_style_radius(obj, 9, 0);

    static lv_style_transition_dsc_t tran;
    static const lv_style_prop_t prop[] = { LV_STYLE_WIDTH, LV_STYLE_HEIGHT, LV_STYLE_PROP_INV};
    lv_style_transition_dsc_init(
            &tran,
            prop,
            lv_anim_path_ease_out,
            200,
            0,
            nullptr
    );
    lv_obj_set_style_transition(obj, &tran, LV_STATE_PRESSED);
    lv_obj_set_style_transition(obj, &tran, LV_STATE_FOCUSED);

    lv_obj_update_layout(obj);

    return obj;
}