//
// Created by 22755 on 2023/11/19.
//

#ifndef LVGL_LIVEMAP_H
#define LVGL_LIVEMAP_H

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// 创建实时地图
// root: 父对象
// tileNum: 瓦片数量
void Live_Map_Create(lv_obj_t* root, uint32_t tileNum);

// 创建样式
void Style_Create();

// 创建地图
// par: 父对象
// tileNum: 瓦片数量
void Map_Create(lv_obj_t* par, uint32_t tileNum);

// 创建缩放控制
// par: 父对象
void ZoomCtrl_Create(lv_obj_t* par);

// 创建运动信息
// par: 父对象
void SportInfo_Create(lv_obj_t* par);

// 卸载实时地图
void livmap_uninstall(void);

// 安装实时地图
void livmap_install(void);

#ifdef __cplusplus
}
#endif

#endif //LVGL_LIVEMAP_H
