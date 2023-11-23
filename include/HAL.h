#ifndef __HAL_H  // 防止头文件重复包含
#define __HAL_H  // 定义宏

#include <Arduino.h>  // 包含Arduino库
#include "HAL.h"  // 包含自定义的HAL库
#ifdef __cplusplus  // 如果是C++编译器
extern "C" {  // 以C语言方式编译
#endif
#include "lvgl.h"  // 包含lvgl库

namespace HAL  // 定义HAL命名空间
{
    void HAL_Init(void);  // HAL初始化函数
    void GPS_Update(void);  // GPS更新函数
    void Time_init(void);  // 时间初始化函数
    void Encoder_Init(void);  // 编码器初始化函数
    int32_t Encoder_GetDiff(void);  // 获取编码器差值函数
}
#ifdef __cplusplus  // 如果是C++编译器
} /*extern "C"*/  // 结束以C语言方式编译
#endif
#endif  // 结束防止头文件重复包含