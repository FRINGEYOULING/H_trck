//
// Created by 22755 on 2023/11/19.
//

#include "Livemap.h"
#include "lvgl.h"
#include "Diplat.h"
#include "animotion.h"
#include "TinyGPS++.h"
struct
{
    lv_obj_t* labelInfo;

    lv_style_t styleCont;
    lv_style_t styleLabel;
    lv_style_t styleLine;

    struct
    {
        lv_obj_t* cont;
        lv_obj_t* imgArrow;
        lv_obj_t** imgTiles;
        uint32_t tileNum;
    } map;

//    struct
//    {
//        lv_obj_t* cont;
//        lv_poly_line* lineTrack;
//        lv_obj_t* lineActive;
//        lv_point_t pointActive[2];
//    } track;

    struct
    {
        lv_obj_t* cont;
        lv_obj_t* labelInfo;
        lv_obj_t* slider;
    } zoom;

    struct
    {
        lv_obj_t* cont;
    } move;

    struct
    {
        lv_obj_t* cont;

        lv_obj_t* labelSpeed;
        lv_obj_t* labelTrip;
        lv_obj_t* labelTime;
    } sportInfo;
} UIR;
extern TinyGPSPlus gps;
char sportt[64];
extern Sport_Time St;
void up_date(lv_timer_t *tmr)
{
    sprintf(sportt,"%02d:%02d:%02d",St.hour,St.min,St.sec);
    lv_label_set_text_fmt(UIR.sportInfo.labelSpeed,"%.1f",gps.speed.kmph());
    lv_label_set_text_fmt(UIR.sportInfo.labelTrip,"%.2f",Trip);
    lv_label_set_text_fmt(UIR.sportInfo.labelTime,"%s",sportt);
}

lv_timer_t *sport_timer;

LV_FONT_DECLARE(font_bahnschrift_17);
LV_FONT_DECLARE(font_bahnschrift_32);
LV_FONT_DECLARE(font_bahnschrift_13);
LV_IMG_DECLARE(img_src_gps_arrow_dark);
LV_IMG_DECLARE(img_src_trip);
LV_IMG_DECLARE(img_src_alarm);
#  define TILE_IMG_CREATE  lv_img_create
#  define TILE_IMG_SET_SRC lv_img_set_src
void Live_Map_Create(lv_obj_t* root, uint32_t tileNum)
{
    lv_obj_set_style_bg_color(root, lv_color_white(), 0);

    // lv_obj_t* label = lv_label_create(root);
    // lv_obj_center(label);
    // lv_obj_set_style_text_font(label, &font_bahnschrift_17, 0);
    // lv_label_set_text(label, "LOADING...");
    // UIR.labelInfo = label;
//
    sport_timer = lv_timer_create(up_date,100,0);
    lv_timer_set_repeat_count(sport_timer,-1);
    Style_Create();
    Map_Create(root, tileNum);
//    ZoomCtrl_Create(root);
    SportInfo_Create(root);
}

lv_obj_t* ImgLabel_Create(lv_obj_t* par, const void* img_src, lv_coord_t x_ofs, lv_coord_t y_ofs)
{
    lv_obj_t* img = lv_img_create(par);
    lv_img_set_src(img, img_src);

    lv_obj_align(img, LV_ALIGN_TOP_MID, 0, y_ofs);

    lv_obj_t* label = lv_label_create(par);
    lv_label_set_text(label, "--");
    lv_obj_add_style(label, &UIR.styleLabel, 0);
    lv_obj_align_to(label, img, LV_ALIGN_OUT_RIGHT_MID, x_ofs, 0);
    return label;
}

void map_uinstall(lv_event_t *e)
{
    livmap_uninstall();
}

void SportInfo_Create(lv_obj_t* par)
{
    /* cont */
    lv_obj_t* obj = lv_obj_create(par);
    lv_obj_remove_style_all(obj);
    lv_obj_add_style(obj, &UIR.styleCont, 0);
    lv_obj_set_size(obj, 159, 66);
    lv_obj_align(obj, LV_ALIGN_BOTTOM_LEFT, -10, 10);
    lv_obj_set_style_radius(obj, 10, 0);
    UIR.sportInfo.cont = obj;

    /* speed */
    lv_obj_t* label = lv_label_create(obj);
    lv_label_set_text(label, "00");
    lv_obj_set_style_text_font(label, &font_bahnschrift_32, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 20, -10);
    UIR.sportInfo.labelSpeed = label;

    label = lv_label_create(obj);
    lv_label_set_text(label, "km/h");
    lv_obj_set_style_text_font(label, &font_bahnschrift_13, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_align_to(label, UIR.sportInfo.labelSpeed, LV_ALIGN_OUT_BOTTOM_MID, 0, 3);

    UIR.sportInfo.labelTrip = ImgLabel_Create(obj, &img_src_trip, 5, 10);
    UIR.sportInfo.labelTime = ImgLabel_Create(obj, &img_src_alarm, 5, 30);
    lv_group_t* group = lv_group_get_default();
    lv_group_add_obj(group, obj);
    lv_obj_add_event_cb(obj,map_uinstall,LV_EVENT_CLICKED,NULL);
}



void ZoomCtrl_Create(lv_obj_t* par)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_add_style(cont, &UIR.styleCont, 0);
    lv_obj_set_style_opa(cont, LV_OPA_COVER, 0);
    lv_obj_set_size(cont, 50, 30);
    lv_obj_set_pos(cont, lv_obj_get_style_width(par, 0) - lv_obj_get_style_width(cont, 0) + 5, 40);
    UIR.zoom.cont = cont;

    static const lv_style_prop_t prop[] =
            {
                    LV_STYLE_X,
                    LV_STYLE_OPA,
                    LV_STYLE_PROP_INV
            };
    static lv_style_transition_dsc_t tran;
    lv_style_transition_dsc_init(&tran, prop, lv_anim_path_ease_out, 200, 0, nullptr);
    lv_obj_set_style_x(cont, lv_obj_get_style_width(par, 0), LV_STATE_USER_1);
    lv_obj_set_style_opa(cont, LV_OPA_TRANSP, LV_STATE_USER_1);
    lv_obj_set_style_transition(cont, &tran, LV_STATE_USER_1);
    lv_obj_set_style_transition(cont, &tran, LV_STATE_DEFAULT);
    lv_obj_add_state(cont, LV_STATE_USER_1);

    lv_obj_t* label = lv_label_create(cont);
    lv_obj_add_style(label, &UIR.styleLabel, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, -2, 0);
    lv_label_set_text(label, "--");
    UIR.zoom.labelInfo = label;

    lv_obj_t* slider = lv_slider_create(cont);
    lv_obj_remove_style_all(slider);
    lv_slider_set_value(slider, 15, LV_ANIM_OFF);
    UIR.zoom.slider = slider;
}

void Style_Create()
{
    lv_style_init(&UIR.styleCont);
    lv_style_set_bg_color(&UIR.styleCont, lv_color_black());
    lv_style_set_bg_opa(&UIR.styleCont, LV_OPA_60);
    lv_style_set_radius(&UIR.styleCont, 6);
    lv_style_set_shadow_width(&UIR.styleCont, 10);
    lv_style_set_shadow_color(&UIR.styleCont, lv_color_black());

    lv_style_init(&UIR.styleLabel);
    lv_style_set_text_font(&UIR.styleLabel, &font_bahnschrift_17);
    lv_style_set_text_color(&UIR.styleLabel, lv_color_white());

    lv_style_init(&UIR.styleLine);
    lv_style_set_line_color(&UIR.styleLine, lv_color_hex(0xff931e));
    lv_style_set_line_width(&UIR.styleLine, 5);
    lv_style_set_line_opa(&UIR.styleLine, LV_OPA_COVER);
    lv_style_set_line_rounded(&UIR.styleLine, true);
}


void Map_Create(lv_obj_t* par, uint32_t tileNum)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    UIR.map.cont = cont;

    UIR.map.imgTiles = (lv_obj_t**)lv_mem_alloc(tileNum * sizeof(lv_obj_t*));
    UIR.map.tileNum = tileNum;

    for (uint32_t i = 0; i < tileNum; i++)
    {
        lv_obj_t* img = TILE_IMG_CREATE(cont);
        lv_obj_remove_style_all(img);
        UIR.map.imgTiles[i] = img;
    }

//    Track_Create(cont);

    lv_obj_t* img = lv_img_create(par);
    lv_img_set_src(img, &img_src_gps_arrow_dark);

    lv_img_t* imgOri = (lv_img_t*)img;
    lv_obj_set_pos(img, 120,120);
    UIR.map.imgArrow = img;
}

lv_obj_t *lmap;

void livmap_install(void)
{
    lv_obj_del(main_home);
    lmap = lv_obj_create(lv_scr_act());
    lv_obj_set_size(lmap,240,240);
    lv_obj_set_style_radius(lmap,0,LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(lmap,LV_SCROLLBAR_MODE_OFF);
    Live_Map_Create(lmap,11);
}

void livmap_uninstall(void)
{
    lv_timer_pause(sport_timer);
    lv_obj_del(lmap);
    Diplat();
    Menu_Load(main_home,LV_SCR_LOAD_ANIM_MOVE_BOTTOM,750,50);
    Menu_state = 0;
}