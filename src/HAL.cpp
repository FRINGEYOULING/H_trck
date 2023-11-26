#include <Arduino.h>
#include <HAL.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "TinyGPS++.h"
#include "Ticker.h"
#include "SysIfo.h"
#include "Start_up.h"
#include "Diplat.h"
#include "Statue_Bar.h"
#include "I2Cdev.h"
#include "Wire.h"
#include <MPU9250.h>
#include <BasicEncoder.h>
BasicEncoder encoder(47, 45); //给编码器的类命名
static volatile int32_t EncoderDiff = 0;
TinyGPSPlus gps;//给GPS的类命名
Ticker lvgl_handel_tick; //声明Ticker对象，中断用于处理桌面信息
Ticker GPS_handle_tick;//中断用于订阅GPS的值

void lvgl_handle_callback() //回调函数
{
    lv_task_handler();
}

MPU9250 accelgyro;//给陀螺仪的类命名
int16_t acx, acy, acz;
int16_t grx, gry, grz;
int16_t mgx, mgy, mgz;
int16_t temp;
void HAL::HAL_Init(void)
{
    Serial.begin(115200);//串口初始化
    Serial2.begin(9600);//gps初始化
    Wire.begin(1,2);//I2C初始化
    Wire.setClock(400000);//I2C时钟设置400KHz
    accelgyro.initialize();//陀螺仪初始化
    // HAL::Time_init();
    //调用图形库
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    Start_UP();//启动动画
    pinMode(48, INPUT_PULLUP);//按键初始化
    lvgl_handel_tick.attach_ms(5, lvgl_handle_callback);//lvgl刷新的中断
    GPS_handle_tick.attach_ms(200, HAL::GPS_Update);//gps信息中断
}

location loc;

char UTC_BUFF[128];
char clock_buff[64];
void HAL::GPS_Update(void)
{
    while (Serial2.available() > 0)
    {
        char c = Serial2.read();
        gps.encode(c);
        // Serial.print(c);
    }
    sprintf(UTC_BUFF,"%d-%d-%d\n%02d:%02d:%02d",gps.date.year(),gps.date.month(),gps.date.day()
        ,gps.time.hour()+8,gps.time.minute(),gps.time.second());
    sprintf(clock_buff,"%02d:%02d",gps.time.hour()+8,gps.time.minute());
    //获取经纬度
    loc.lat = gps.location.lat();
    loc.lnt = gps.location.lng();
//    loc.d_lat = loc.lat - loc.l_lat;//纬度差
//    loc.d_lnt = loc.lnt - loc.l_lnt;//经度差
    //经纬度距离计算公式换算成米
    loc.distance = gps.distanceBetween(loc.lat,loc.lnt,loc.l_lat,loc.l_lnt);
    Now_Speed  = gps.speed.kmph();
    if(Sport_Statue==1)
    {
        if(Now_Speed>Max_Speed)Max_Speed = Now_Speed;
    }
    accelgyro.getMotion9(&acx, &acy, &acz, &grx, &gry, &grz, &mgx, &mgy, &mgz);
    temp = accelgyro.getTemperature();
    loc.l_lat = loc.lat;
    loc.l_lnt = loc.lnt;
}

hw_timer_t *tim1 = NULL;

void tim1Interrupt()
{//中断服务函数
//     HAL::GPS_Update();

}


int32_t HAL::Encoder_GetDiff()
{
    encoder.service();
    int encoder_change = encoder.get_change();
    if (encoder_change) {
        EncoderDiff = encoder.get_count();
        encoder.reset();
    } 
    int32_t diff = EncoderDiff;
    EncoderDiff = 0;
    return diff;
}

void HAL::Time_init(void)
{
    tim1 = timerBegin(0, 240, true);
    timerAttachInterrupt(tim1, tim1Interrupt, true);
    timerAlarmWrite(tim1, 1000000ul, true);
    timerAlarmEnable(tim1);
}
