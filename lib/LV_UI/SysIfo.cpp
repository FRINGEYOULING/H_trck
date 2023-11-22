//
// Created by 22755 on 2023/11/15.
//
#include "SysIfo.h"
#include "lvgl.h"
#include "Diplat.h"
LV_IMG_DECLARE(img_src_system_info);
LV_IMG_DECLARE(img_src_bicycle);
LV_IMG_DECLARE(img_src_storage);
LV_IMG_DECLARE(img_src_battery_info);
LV_IMG_DECLARE(img_src_time_info);
LV_IMG_DECLARE(img_src_map_location);
LV_IMG_DECLARE(img_src_gyroscope);
LV_IMG_DECLARE(img_src_compass);
LV_FONT_DECLARE(font_bahnschrift_17);
LV_FONT_DECLARE(font_bahnschrift_13);
#define ITEM_HEIGHT_MIN   100
#define ITEM_PAD          ((LV_VER_RES - ITEM_HEIGHT_MIN) / 2)


struct
{
    item_t sport;
    item_t gps;
    item_t mag;
    item_t imu;
    item_t rtc;
    item_t battery;
    item_t storage;
    item_t system;
} ui;

typedef struct {
    lv_style_t icon;
    lv_style_t info;
    lv_style_t data;
    lv_style_t focus;
}Style_class;

Style_class style;
lv_obj_t* root;
void Create()
{
    root = lv_obj_create(lv_scr_act());
    lv_obj_set_size(root,240,240);
    lv_obj_set_style_border_width(root,0,LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(root,LV_SCROLLBAR_MODE_OFF );
    lv_obj_set_style_pad_ver(root, ITEM_PAD, 0);
    lv_obj_set_style_bg_color(root, lv_color_hex(0x000000), LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(root, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
            root,
            LV_FLEX_ALIGN_START,
            LV_FLEX_ALIGN_START,
            LV_FLEX_ALIGN_CENTER
    );

    Style_Init();

//    /* Item Sport */
    Item_Create(
            &ui.sport,
            root,
            "Sport",
            &img_src_bicycle,

            "Total trip\n"
            "Total time\n"
            "Max speed"
    );
//
//    /* Item GPS */
    Item_Create(
            &ui.gps,
            root,
            "GPS",
            &img_src_map_location,

            "Latitude\n"
            "Longitude\n"
            "Altitude\n"
            "UTC Time\n\n"
            "Course\n"
            "Speed"
    );
//
//    /* Item MAG */
    Item_Create(
            &ui.mag,
            root,
            "MAG",
            &img_src_compass,

            "Compass\n"
            "X\n"
            "Y\n"
            "Z"
    );
//
//    /* Item IMU */
    Item_Create(
            &ui.imu,
            root,
            "IMU",
            &img_src_gyroscope,
            "Step\n"
            "Ax\n"
            "Ay\n"
            "Az\n"
            "Gx\n"
            "Gy\n"
            "Gz"
    );
//
//    /* Item RTC */
    Item_Create(
            &ui.rtc,
            root,
            "RTC",
            &img_src_time_info,

            "Date\n"
            "Time"
    );
//
//    /* Item Battery */
    Item_Create(
            &ui.battery,
            root,
            "Battery",
            &img_src_battery_info,

            "Usage\n"
            "Voltage\n"
            "Status"
    );
//
//    /* Item Storage */
    Item_Create(
            &ui.storage,
            root,
            "Storage",
            &img_src_storage,

            "Status\n"
            "Size\n"
            "Type\n"
            "Version"
    );
//
//    /* Item System */
    Item_Create(
            &ui.system,
            root,
            "System",
            &img_src_system_info,

            "Firmware\n"
            "Author\n"
            "LVGL\n"
            "SysTick\n"
            "Compiler\n\n"
            "Build\n"
    );

    Group_Init();
}



void onFocus(lv_group_t* g)
{
    lv_obj_t* icon = lv_group_get_focused(g);
    lv_obj_t* cont = lv_obj_get_parent(icon);
    lv_coord_t y = lv_obj_get_y(cont);
    lv_obj_scroll_to_y(lv_obj_get_parent(cont), y, LV_ANIM_ON);
}

void Group_Init()
{
    lv_group_t* group = lv_group_get_default();
    lv_group_set_wrap(group, true);
    lv_group_set_focus_cb(group, onFocus);

    item_t* item_grp = ((item_t*)&ui);

    /* Reverse adding to group makes encoder operation more comfortable */
    for (int i = sizeof(ui) / sizeof(item_t) - 1; i >= 0; i--)
    {
        lv_group_add_obj(group, item_grp[i].icon);
    }

    lv_group_focus_obj(item_grp[0].icon);
}

void SetScrollToY(lv_obj_t* obj, lv_coord_t y, lv_anim_enable_t en)
{
    lv_coord_t scroll_y = lv_obj_get_scroll_y(obj);
    lv_coord_t diff = -y + scroll_y;

    lv_obj_scroll_by(obj, 0, diff, en);
}



void Style_Init()
{
    lv_style_init(&style.icon);
    lv_style_set_width(&style.icon, 220);
    lv_style_set_bg_color(&style.icon, lv_color_black());
    lv_style_set_bg_opa(&style.icon, LV_OPA_COVER);
    lv_style_set_text_font(&style.icon, &font_bahnschrift_17);
    lv_style_set_text_color(&style.icon, lv_color_white());

    lv_style_init(&style.focus);
    lv_style_set_width(&style.focus, 70);
    lv_style_set_border_side(&style.focus, LV_BORDER_SIDE_RIGHT);
    lv_style_set_border_width(&style.focus, 2);
    lv_style_set_border_color(&style.focus, lv_color_hex(0xff931e));

    static const lv_style_prop_t style_prop[] =
            {
                    LV_STYLE_WIDTH,
                    LV_STYLE_PROP_INV
            };

    static lv_style_transition_dsc_t trans;
    lv_style_transition_dsc_init(
            &trans,
            style_prop,
            lv_anim_path_overshoot,
            200,
            0,
            nullptr
    );
    lv_style_set_transition(&style.focus, &trans);
    lv_style_set_transition(&style.icon, &trans);

    lv_style_init(&style.info);
    lv_style_set_text_font(&style.info, &font_bahnschrift_17);
    lv_style_set_text_color(&style.info, lv_color_hex(0x999999));

    lv_style_init(&style.data);
    lv_style_set_text_font(&style.data, &font_bahnschrift_13);
    lv_style_set_text_color(&style.data, lv_color_white());
}

void Style_Reset()
{
    lv_style_reset(&style.icon);
    lv_style_reset(&style.info);
    lv_style_reset(&style.data);
    lv_style_reset(&style.focus);
}


void Item_Create(
        item_t* item,
        lv_obj_t* par,
        const char* name,
        const void* img_src,
        const char* infos
)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_enable_style_refresh(false);
    lv_obj_remove_style_all(cont);
    lv_obj_set_width(cont, 220);

    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    item->cont = cont;

    /* icon */
    lv_obj_t* icon = lv_obj_create(cont);
    lv_obj_enable_style_refresh(false);
    lv_obj_remove_style_all(icon);
    lv_obj_clear_flag(icon, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_style(icon, &style.icon, 0);
    lv_obj_add_style(icon, &style.focus, LV_STATE_FOCUSED);
    lv_obj_set_style_align(icon, LV_ALIGN_LEFT_MID, 0);

    lv_obj_set_flex_flow(icon, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
            icon,
            LV_FLEX_ALIGN_SPACE_AROUND,
            LV_FLEX_ALIGN_CENTER,
            LV_FLEX_ALIGN_CENTER
    );

    lv_obj_t* img = lv_img_create(icon);
    lv_obj_enable_style_refresh(false);
    lv_img_set_src(img, img_src);

    lv_obj_t* label = lv_label_create(icon);
    lv_obj_enable_style_refresh(false);
    lv_label_set_text(label, name);
    item->icon = icon;

    /* infos */
    label = lv_label_create(cont);
    lv_obj_enable_style_refresh(false);
    lv_label_set_text(label, infos);
    lv_obj_add_style(label, &style.info, 0);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 75, 0);
    item->labelInfo = label;

    /* datas */
    label = lv_label_create(cont);
    lv_obj_enable_style_refresh(false);
    lv_label_set_text(label, "-");
    lv_obj_add_style(label, &style.data, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 60, 0);
    item->labelData = label;

    lv_obj_move_foreground(icon);
    lv_obj_enable_style_refresh(true);

    /* get real max height */
    lv_obj_update_layout(item->labelInfo);
    lv_coord_t height = lv_obj_get_height(item->labelInfo);
    height = LV_MAX(height, ITEM_HEIGHT_MIN);
    lv_obj_set_height(cont, height);
    lv_obj_set_height(icon, height);
}
