
#include "tim.h"

void TIMDelay_Config(){
	
	RCC_APB2PeriphClockCmd(TIMER_DElAY_RCC,ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 0xFFFF-1;
	TIM_InitStruct.TIM_Prescaler = 16800-1;
	TIM_TimeBaseInit(TIM1,&TIM_InitStruct);
	TIM_Cmd(TIMER_DElAY,ENABLE);

}
void TIMPWM_Config(){
	/*Cap xung clock cho TIM2*/
	RCC_APB1PeriphClockCmd(TIMER_PWM_RCC,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	
	/* */
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
	/* */
	TIM_TimeBaseInitTypeDef TIM2_InitStruct;
	TIM2_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM2_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM2_InitStruct.TIM_Period = 20000-1;
	TIM2_InitStruct.TIM_Prescaler = 83;
	TIM_TimeBaseInit(TIM2,&TIM2_InitStruct);
	
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1000-1; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_Cmd(TIM2, ENABLE);
  TIM_ARRPreloadConfig(TIM2, ENABLE);

}

void Delay_ms(uint32_t time){
	TIM_SetCounter(TIMER_DElAY,0);
	while(TIM_GetCounter(TIMER_DElAY) < time*10);
}

void Delay_us(uint32_t u32DelayInUs)
{
	TIM_SetCounter(TIM1, 0);
	while(TIM_GetCounter(TIM3) < u32DelayInUs);
}

void set_pwm(uint32_t time_pwm){
	TIM_SetCompare2(TIMER_PWM,time_pwm);
	
}
void Delay_Init(void)
{
	TIMDelay_Config();
}

