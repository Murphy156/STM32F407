/**
  ******************************************************************************
  * @file    bsp_bldcm_control.c
  * @author  Leo
  * @version V1.0
  * @date    2023-10-23
  * @brief   无刷电机控制接口
  ******************************************************************************
  */
#include "bsp_bldcm_control.h"

/** 私有变量 */
static bldcm_data_t motor1_bldcm_data;
static bldcm_data_t motor2_bldcm_data;

/**
  * @brief  电机初始化
  * @param  无
  * @retval 无
  */
void bldcm_init(void)
{
    TIMx_Configuration();           /** 电机控制定时器，引脚初始化 */
    hall_motor_tim_config();       /** 霍尔传感器初始化 */
}

/**
  * @brief  设置电机速度
  * @param  v: 速度（占空比）
  * @retval 无
  */
void set_motor1_bldcm_speed(uint16_t v)
{
    motor1_bldcm_data.dutyfactor = v;

    set_motor1_pwm_pulse(v);     // 设置速度
}

void set_motor2_bldcm_speed(uint16_t v)
{
    motor2_bldcm_data.dutyfactor = v;

    set_motor2_pwm_pulse(v);     // 设置速度
}

/**
  * @brief  设置电机方向
  * @param  无
  * @retval 无
  */
void set_motor1_bldcm_direction(motor_dir_t dir)
{
    motor1_bldcm_data.direction = dir;
}

void set_motor2_bldcm_direction(motor_dir_t dir)
{
    motor2_bldcm_data.direction = dir;
}

/**
  * @brief  获取电机当前方向
  * @param  无
  * @retval 无
  */
motor_dir_t get_motor1_bldcm_direction(void)
{
    return motor1_bldcm_data.direction;
}

motor_dir_t get_motor2_bldcm_direction(void)
{
    return motor2_bldcm_data.direction;
}

/**
  * @brief  使能电机
  * @param  无
  * @retval 无
  */
void set_motor1_bldcm_enable(void)
{
    hall_motor_enable();
}

void set_motor2_bldcm_enable(void)
{
    hall_motor_enable();
}

/**
  * @brief  禁用电机
  * @param  无
  * @retval 无
  */
void set_motor1_bldcm_disable(void)
{
    /** 禁用霍尔传感器接口 */
    hall_motor_disable();

    /** 停止 PWM 输出 */
    stop_motor1_pwm_output();
}

void set_motor2_bldcm_disable(void)
{
    /** 禁用霍尔传感器接口 */
    hall_motor_disable();

    /** 停止 PWM 输出 */
    stop_motor2_pwm_output();
}

/*********************************************END OF FILE**********************/
