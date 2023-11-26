//
// Created by 22755 on 2023/11/15.
//

#include <Diplat.h>
#include "lvgl.h"
#include <animotion.h>
#include "SysIfo.h"
#include "Ticker.h"
#include "Statue_Bar.h"
#include "TinyGPS++.h"
#include "Livemap.h"
extern location loc;
LV_FONT_DECLARE(font_bahnschrift_65);
LV_FONT_DECLARE(font_bahnschrift_17);
LV_FONT_DECLARE(font_bahnschrift_13);
LV_IMG_DECLARE(img_src_menu);
LV_IMG_DECLARE(img_src_locate);
LV_IMG_DECLARE(img_src_pause);
LV_IMG_DECLARE(img_src_start);
LV_IMG_DECLARE(img_src_stop);
LV_IMG_DECLARE(img_Adream);
#define Sysinfo 1
#define map_loca 2
lv_obj_t *main_home;
uint8_t Menu_state = 0;
Ticker Sport_Tick;
typedef struct {
    lv_obj_t* menu;
    lv_obj_t *start;
    lv_obj_t *locat;
}Button_num;

uint8_t Sport_Statue = 0;

typedef struct 
{
    lv_obj_t* Speed;
    lv_obj_t* AVG;
    lv_obj_t* Time;
    lv_obj_t* Trip;
    lv_obj_t* Calorie;
}Untxt_num;

typedef struct
{
    float Avg_speed;
    float Trip;
    float Calorie_num;
}Sport_mation;

typedef struct
{
    float AVG;
    Sport_Time time;
    float Trip;
    float Calorie;
}Last_Date;
Last_Date Last_date;
Sport_mation sport_num;
Untxt_num unit;
extern TinyGPSPlus gps;
Button_num button;
lv_group_t *btn_group;
lv_timer_t *update;

int cnt = 0;
float full_speed = 0;
float Trip = 0;
void Sub_Date(lv_timer_t *tmr)
{
    Trip += loc.distance/1000;
    lv_label_set_text_fmt(unit.Speed,"%.1f",gps.speed.kmph());
    lv_label_set_text_fmt(unit.Trip,"%.2f",Trip);
    lv_label_set_text_fmt(unit.Calorie,"%.2f",(Trip)*0.6142*75);
    cnt++;
    full_speed+=gps.speed.kmph();
    if(cnt>=9)
    {
        sport_num.Avg_speed = full_speed/10;
        lv_label_set_text_fmt(unit.AVG,"%.2f",sport_num.Avg_speed);
        full_speed = 0;
        cnt = 0;
    }
    Last_date.AVG = sport_num.Avg_speed;
    Last_date.Calorie = (Trip)*0.6142*75;
    Last_date.Trip = Trip;
}

static void Btn_event(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    if(obj == button.menu)
    {
        if(update!=NULL)
        {
            lv_timer_pause(update);
        }
        Sysinfo_install();
        Menu_state = 1;
    }
    if(obj == button.locat)
    {
        if(update!=NULL)
        {
            lv_timer_pause(update);
        }
        livmap_install();
        Menu_state = 2;
    }
    if(obj == button.start)
    {
        if(code == LV_EVENT_LONG_PRESSED)
        {
           if(gps.satellites.value()!=0&&Sport_Statue==0)
            {
                lv_label_set_text_fmt(s_statue,"REC");
                lv_timer_resume(update);
                lv_obj_set_style_bg_img_src(button.start, &img_src_stop, 0);
                Sport_Statue = 1;
            }
            else if(Sport_Statue==1)
            {
                lv_label_set_text_fmt(s_statue,"   ");
                lv_obj_set_style_bg_img_src(button.start, &img_src_start, 0);
                lv_timer_pause(update);
                lv_label_set_text_fmt(unit.Speed,"00");
                Sport_Statue = 0;
            } 
        }
        
    }
}
uint8_t S=0;
uint8_t H = 0;
uint8_t M = 0;

Sport_Time St;

void Sport_Handle()
{
    if(Sport_Statue==1)
    {
        St.sec++;
        if(St.sec==60)
        {
            St.min++;
            St.sec=0;
        }
        if(St.min==60)
        {
            St.hour++;
            St.min=0;
        }
        if(St.hour==99)
        {
            St.hour = 99;
        }
        if(Menu_state==0)
        {
            lv_label_set_text_fmt(unit.Time,"%02d:%02d:%02d",St.hour,St.min,St.sec);
        }
        Last_date.time.hour = St.hour;
        Last_date.time.min = St.min;
        Last_date.time.sec = St.sec;
    }
}

void Ticke_init()
{
    Sport_Tick.attach(1,Sport_Handle);
}
uint8_t dateInital_flag = 0;
//初始化值
void Style_Num_Init()
{
    if(dateInital_flag==0)
    {
        lv_label_set_text_fmt(unit.AVG,"%.2f",0.00);
        lv_label_set_text_fmt(unit.Time,"%02d:%02d:%02d",00,00,00);
        lv_label_set_text_fmt(unit.Trip,"%.2f",0.00);
        lv_label_set_text_fmt(unit.Calorie,"%.2f",0.00);
        dateInital_flag = 1;
    }
    else
    {
        lv_label_set_text_fmt(unit.Trip,"%.2f",Last_date.Trip);
        lv_label_set_text_fmt(unit.Calorie,"%.2f",Last_date.Calorie);
        lv_label_set_text_fmt(unit.AVG,"%.2f",Last_date.AVG);
        lv_label_set_text_fmt(unit.Time,"%02d:%02d:%02d",Last_date.time.hour,
                            Last_date.time.min,Last_date.time.sec);
    }
}

void Diplat()
{
    main_home = lv_img_create(lv_scr_act());
    lv_obj_remove_style_all(main_home);
    lv_obj_set_size(main_home,240,240);
    lv_obj_set_scrollbar_mode(main_home,LV_SCROLLBAR_MODE_OFF );
//    lv_obj_clear_flag(main_home, LV_OBJ_FLAG_SCROLLABLE);
//    lv_obj_set_style_bg_color(main_home,lv_color_hex(0x000000),LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(main_home,0,LV_STATE_DEFAULT);
    lv_img_set_src(main_home,&img_Adream);
    lv_obj_center(main_home);
    lv_anim_t ani_foce;
    lv_anim_init(&ani_foce);
    lv_obj_t *main_force = lv_obj_create(main_home);
    lv_obj_set_align(main_force,LV_ALIGN_TOP_MID);
    lv_obj_set_size(main_force,240,0);
    lv_obj_set_style_border_width(main_force,0,LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(main_force,LV_SCROLLBAR_MODE_OFF );
    lv_obj_set_style_bg_color(main_force,lv_color_hex(0x363636),LV_STATE_DEFAULT);
    lv_obj_set_style_radius(main_force,15,LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(main_force,95,LV_STATE_DEFAULT);
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
    unit.Speed = home_lable;
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
    Style_Num_Init();
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
    update = lv_timer_create(Sub_Date,50,0);
    lv_timer_set_repeat_count(update,-1);
    if(Sport_Statue==1)
    {
        button.start = Btn_Create(btn_cont,&img_src_stop, 0);
        lv_timer_resume(update);
    }
    else
    {
        button.start = Btn_Create(btn_cont,&img_src_start, 0);
        lv_timer_pause(update);
    }
    button.locat = Btn_Create(btn_cont,&img_src_locate, -70);    
    btn_group = lv_group_get_default();
    lv_group_add_obj(btn_group,button.start);
    lv_group_add_obj(btn_group,button.menu);
    lv_group_add_obj(btn_group,button.locat);
    lv_group_focus_obj(button.start);
    lv_obj_add_event_cb(button.menu,Btn_event,LV_EVENT_CLICKED,NULL);
    lv_obj_add_event_cb(button.start,Btn_event,LV_EVENT_LONG_PRESSED,NULL);
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
    lv_obj_set_style_text_color(label, lv_color_hex(0x93C4EC), 0);
    if(strcmp(unitText,"AVG")==0)
        unit.AVG = label;
    else if(strcmp(unitText,"Time")==0)
        unit.Time = label;
    else if(strcmp(unitText,"Trip")==0)
        unit.Trip = label;
    else if(strcmp(unitText,"Calorie")==0)
        unit.Calorie = label;
    label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, &font_bahnschrift_13, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x93C4EC), 0);
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

    lv_obj_set_style_bg_opa(obj, LV_OPA_40, 0);
    lv_obj_set_style_width(obj, 45, LV_STATE_PRESSED);
    lv_obj_set_style_height(obj, 25, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x666666), 0);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x93C4EC), LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xEC18A8), LV_STATE_FOCUSED);
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