#ifndef __TIM_H__
#define __TIM_H__

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx.h"
/* Exported macro ------------------------------------------------------------*/
#define  TIMER_DElAY        TIM1
#define  TIMER_DElAY_RCC    RCC_APB2Periph_TIM1
#define  TIMER_PWM        	TIM2
#define  TIMER_PWM_RCC    	RCC_APB1Periph_TIM2

/* Exported functions ------------------------------------------------------- */
void TIMDelay_Config();
void Delay_Init();
void TIMPWM_Config();
void Delay_ms(uint32_t time);
void Delay_us(uint32_t u32DelayInUs);
void set_pwm(uint32_t time_pwm);
#endif /*__TIM_H__*/