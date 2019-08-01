#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP
#include "lpf.h"
#include "sinewave.h"

#define Fs 1000
#define F  10
#define NF 50

extern void SystemClock_Config(void) ; 
uint32_t freq ; 
sine_generator_q15_t signal , noise_set ; 
q15_t filtered,noise,disturbed,sine ; 

int main()
{
	
	HAL_Init() ; 
	SystemClock_Config() ; 
	
	sine_generator_init_q15(&signal,F,Fs) ; 
	sine_generator_init_q15(&noise_set,NF,Fs) ; 
	
	lpf_init() ; 
	
	freq = HAL_RCC_GetHCLKFreq() ; 
	
		while(1) 
		{
				sine = sine_calc_sample_q15(&signal)/2;
				noise= sine_calc_sample_q15(&noise_set)/6 ;
				disturbed = sine + noise ;
				filtered = lpfilter(&disturbed) ; 
			  HAL_Delay(1) ; 
		}


}


void SysTick_Handler(void)
{
	HAL_IncTick() ; 
	HAL_SYSTICK_IRQHandler() ; 
}

