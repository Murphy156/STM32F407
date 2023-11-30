#ifndef CPROJECT_BSP_USART_H
#define CPROJECT_BSP_USART_H

#include "stm32f4xx.h"
#include <stdio.h>

/** 串口波特率 */
#define USART_BAUDRATE					115200

/** 引脚定义 */
/*************************************/
#define USART_SEL						USART1
#define USART_CLK_ENABLE()				__USART1_CLK_ENABLE();

#define USART_RX_GPIO_PORT              GPIOB
#define USART_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define USART_RX_PIN                    GPIO_PIN_6
#define USART_RX_AF                     GPIO_AF7_USART1

#define USART_TX_GPIO_PORT              GPIOB
#define USART_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define USART_TX_PIN                    GPIO_PIN_7
#define USART_TX_AF                     GPIO_AF7_USART1

#define USART_IRQHandler                USART1_IRQHandler
#define USART_IRQ                 		USART1_IRQn

/** 数据接收缓冲区大小 */
#define min_protocol_length	            8
#define	max_protocol_length	            16
#define	max_length		                (min_protocol_length * max_protocol_length) /**乘法一定要加括号，16*8 = 128 */

/** 帧头 */
#define PACK_HEADER						0x55AA


/** 指令 （上位机 -> 下位机）*/
#define SetPIDValue_CMD				    0x10			/** 设置PID参数命令 */
#define SpeedGo_CMD						0x11			/** 使能速度命令 */
#define LocationGo_CMD				    0x12			/** 使能位置命令 */
#define TurnLeft_CMD					0x13			/** 左转命令 */
#define Stop_CMD					    0x14			/** 停止命令 */
#define TurnRight_CMD    			    0x15			/** 右转命令 */
#define Reset_CMD 						0x16			/** 重置命令 */


/** 指令 （下位机 -> 上位机）*/
#define Send_Speed_CMD                  0x17			/** 发送速度数据命令 */
#define Send_Location_CMD			    0x18			/** 发送位置数据命令 */

/** 空指令 */
#define CMD_NONE             	        0xFF            /** 空指令 */

extern UART_HandleTypeDef UartHandle;


#endif //CPROJECT_BSP_USART_H
