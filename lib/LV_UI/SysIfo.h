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
extern uint8_t Now_Speed;
extern uint8_t Max_Speed;
void Style_Init();
void Sysinfo_unint();
void Sysinfo_install();
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
void Time_reset(uint32_t period,int32_t repeat_count);
class Sys_Registe
{
    public:
    void SetSport(//设置运动信息
    float trip,
    const char* time,
    float maxSpd);

    void SetGPS(//设置GPS信息
    float lat,
    float lng,
    float alt,
    const char* utc,
    float course,
    float speed);

    void SetMAG(//设置磁力计信息
    float dir,
    int x,
    int y,
    int z);

    void SetIMU(//设置IMU信息
    int step,
    const char* info);

    void SetRTC(//设置RTC信息
    const char* dateTime);

    void SetBattery(//设置电池信息
    int usage,
    float voltage,
    const char* state);

    void SetStorage(//设置存储信息
    const char* detect,
    const char* size,
    const char* type,
    const char* version);

    void SetSystem(//设置系统信息
    const char* firmVer,
    const char* authorName,
    const char* lvglVer,
    unsigned long bootTime,
    const char* compilerName,
    const char* bulidTime);

};


#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif //LVGL_SYSIFO_H
