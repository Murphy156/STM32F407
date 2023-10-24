#ifndef CPROJECT_BSP_BLDCM_CONTROL_H
#define CPROJECT_BSP_BLDCM_CONTROL_H

#include "stm32f4xx.h"
#include "bsp_motor_tim.h"
#include "main.h"


/** 电机方向控制枚举 */
typedef enum
{
    MOTOR_FWD = 0,
    MOTOR_REV,
}motor_dir_t;

typedef struct
{
    motor_dir_t direction;    /** 电机方向 */
    uint16_t dutyfactor;      /** PWM 输出占空比 */
    uint8_t is_enable;        /** 使能电机 */
    uint32_t lock_timeout;    /** 电机堵转计时 */
}bldcm_data_t;

void bldcm_init(void);

void set_motor1_bldcm_speed(uint16_t v);
void set_motor1_bldcm_direction(motor_dir_t dir);
motor_dir_t get_motor1_bldcm_direction(void);
void set_motor1_bldcm_enable(void);
void set_motor1_bldcm_disable(void);

void set_motor2_bldcm_speed(uint16_t v);
void set_motor2_bldcm_direction(motor_dir_t dir);
motor_dir_t get_motor2_bldcm_direction(void);
void set_motor2_bldcm_enable(void);
void set_motor2_bldcm_disable(void);



#endif //CPROJECT_BSP_BLDCM_CONTROL_H
