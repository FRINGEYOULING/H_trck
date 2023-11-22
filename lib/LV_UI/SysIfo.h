//
// Created by 22755 on 2023/11/15.
//

#ifndef LVGL_SYSIFO_H
#define LVGL_SYSIFO_H
#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl.h"
extern lv_obj_t* root;
typedef struct
{
    lv_obj_t* cont;
    lv_obj_t* icon;
    lv_obj_t* labelInfo;
    lv_obj_t* labelData;
} item_t;
void Style_Init();
void Style_Reset();
void Group_Init();
void Create();
void Item_Create(
        item_t* item,
        lv_obj_t* par,
        const char* name,
        const void* img_src,
        const char* infos
);
#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif //LVGL_SYSIFO_H
