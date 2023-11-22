//
// Created by 22755 on 2023/11/19.
//

#ifndef LVGL_LIVEMAP_H
#define LVGL_LIVEMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"



void Live_Map_Create(lv_obj_t* root, uint32_t tileNum);
void Style_Create();
void Map_Create(lv_obj_t* par, uint32_t tileNum);
void ZoomCtrl_Create(lv_obj_t* par);
void SportInfo_Create(lv_obj_t* par);
void livmap_uninstall(void);
void livmap_install(void);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //LVGL_LIVEMAP_H
