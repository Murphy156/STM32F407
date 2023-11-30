/**
  ******************************************************************************
  * @file   : main.c
  * @brief  : Main program body
  * question: 如果cmake不见了，在file->setting->cmake 中的右上角reload一下即可
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "spi.h"
#include "gpio.h"
#include "bsp_DRV8303.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_bldcm_control.h"
#include "bsp_usart.h"

//void MX_FREERTOS_Init(void);


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    __IO uint16_t MOTOR1_ChannelPulse = MOTOR1_PWM_MAX_PERIOD_COUNT/10;
    __IO uint16_t MOTOR2_ChannelPulse = MOTOR2_PWM_MAX_PERIOD_COUNT/10;

    uint8_t i = 0;
    uint8_t j = 0;

    uint8_t motor1_en_flag = 0;
    uint8_t motor2_en_flag = 0;
    HAL_Init();
    /** 初始化系统时钟为168MHz */
    SystemClock_Config();
    /** LED 灯初始化 */
    LED_GPIO_Config();
    /** 初始化 DRV8303 */
    DRV8303_Init();
    /** 初始化按键G PIO */
    Key_GPIO_Config();
    /** 初始化电机 */
//    bldcm_init();
    /** 初始化USART 配置模式为 115200 8-N-1，中断接收 */
    USART_Config();

    while (1)
    {
        receiving_process();
//        /** 扫描KEY1 */
//        if(Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
//        {
//            LED1_TOGGLE;
//            /** 使能电机 */
//            if(!motor1_en_flag)
//            {
//                set_motor1_bldcm_speed(MOTOR1_ChannelPulse);
//                set_motor1_bldcm_enable();
//            }
//            else
//            {
//                set_motor1_bldcm_disable();
//            }
//            motor1_en_flag = !motor1_en_flag;
//        }
//        /** 扫描KEY2 */
//        if(Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
//        {
//            LED2_TOGGLE;
//            /** 使能电机 */
//            if(!motor2_en_flag)
//            {
//                set_motor2_bldcm_speed(MOTOR2_ChannelPulse);
//                set_motor2_bldcm_enable();
//            }
//            else
//            {
//                set_motor2_bldcm_disable();
//            }
//            motor2_en_flag = !motor2_en_flag;
//        }
//        /** 扫描KEY3 */
//        if(Key_Scan(KEY3_GPIO_PORT, KEY3_PIN) == KEY_ON)
//        {
//            LED3_TOGGLE;
//            /** 增大占空比 */
//            MOTOR1_ChannelPulse += 200;
//
//            if(MOTOR1_ChannelPulse > MOTOR1_PWM_MAX_PERIOD_COUNT)
//                MOTOR1_ChannelPulse = MOTOR1_PWM_MAX_PERIOD_COUNT;
//
//            set_motor1_bldcm_speed(MOTOR1_ChannelPulse);
//
//            MOTOR2_ChannelPulse += 350;
//
//            if(MOTOR2_ChannelPulse > MOTOR2_PWM_MAX_PERIOD_COUNT)
//                MOTOR2_ChannelPulse = MOTOR2_PWM_MAX_PERIOD_COUNT;
//
//            set_motor2_bldcm_speed(MOTOR2_ChannelPulse);
//        }
//        /** 扫描KEY4 */
//        if(Key_Scan(KEY4_GPIO_PORT, KEY4_PIN) == KEY_ON)
//        {
//            LED4_TOGGLE;
//            /** 减少占空比 */
//            if(MOTOR1_ChannelPulse < MOTOR1_PWM_MAX_PERIOD_COUNT/10)
//                MOTOR1_ChannelPulse = 0;
//            else
//                MOTOR1_ChannelPulse -= 350;
//
//            set_motor1_bldcm_speed(MOTOR1_ChannelPulse);
//
//            if(MOTOR2_ChannelPulse < MOTOR2_PWM_MAX_PERIOD_COUNT/10)
//                MOTOR2_ChannelPulse = 0;
//            else
//                MOTOR2_ChannelPulse -= MOTOR2_PWM_MAX_PERIOD_COUNT/10;
//
//            set_motor2_bldcm_speed(MOTOR2_ChannelPulse);
//        }
//        /** 扫描KEY5 */
//        if(Key_Scan(KEY5_GPIO_PORT,KEY5_PIN) == KEY_ON)
//        {
//            LED1_TOGGLE;
//            LED2_TOGGLE;
//            /** 转换方向 */
//            set_motor1_bldcm_direction( (++i % 2) ? MOTOR_FWD : MOTOR_REV);
//
//            set_motor2_bldcm_direction( (++j % 2) ? MOTOR_FWD : MOTOR_REV);
//        }
    }
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* The voltage scaling allows optimizing the power consumption when the device is
       clocked below the maximum system frequency, to update the voltage scaling value
       regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }

    /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
    if (HAL_GetREVID() == 0x1001)
    {
        /* Enable the Flash prefetch */
        __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}
/****************************END OF FILE***************************/

