#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIG_LEN 320 
#define NUM_TAPS 29 
#define BLOCK 32 

uint32_t freq ; 
uint32_t count ; 
float32_t sample , out ; 
static float32_t FIR[BLOCK + NUM_TAPS -1] ;  

uint32_t numBlocks = SIG_LEN/BLOCK ; 
extern void SystemClock_Config(void) ; 
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LEN] ; 
float32_t outputSignal_f32[SIG_LEN] ; 
void plot_input_signal() ; 
void plot_output_signal() ;
void plot() ; 

const float32_t firCoeffs32[NUM_TAPS] = {
  -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
  -0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
  +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
  +0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};

/**
							@NOTE  
											1. THE ARM DSP LIB FILTERS SIGNALS IN BLOCKS , SO DEFINE SIZE ABOVE 

											2. THE FILTER FUNCTION IN DSP LIB REQUIRES AN INTERMEDIATE ARRAY with SIZE = BLOCKSIZE + TAP - 1 to store intermediate results 

											3. DEFINE AN ARRAY TO STORE OUTPUT SIGNALS 
**/  
int main(void)
{
	
	HAL_Init() ;
	SystemClock_Config() ; 	
	
	arm_fir_instance_f32 _in_sig ; 
	arm_fir_init_f32(&_in_sig,NUM_TAPS,(float32_t *)&firCoeffs32[0],(float32_t *)&FIR[0], BLOCK) ;
	int i ;
	
	for(i=0 ; i<numBlocks ; i++)
	arm_fir_f32(&_in_sig,(float *) &inputSignal_f32_1kHz_15kHz[0] + (i*BLOCK) , (float *) &outputSignal_f32[0] + (i*BLOCK), BLOCK) ;  
//	
//	plot_input_signal() ; 
//	plot_output_signal() ;
//		plot() ;

	while(1) 
	{
		
			//plot_input_signal() ; 
			//plot_output_signal() ;
		 	
		plot() ; 
	
		
				//	plot_input_signal() ; 
		
	}

}

void plot_input_signal(void)
{
	
	int i , j ; 
	for(i=0;i<SIG_LEN;i++)
		{
			sample = inputSignal_f32_1kHz_15kHz[i] ; 
			for(j=0 ; j<3000 ; j++) ; 
		}
		if(i==SIG_LEN-1) i=0 ; 
}

void plot_output_signal(void)
{
	
	int i , j ; 
	for(i=0;i<SIG_LEN;i++)
		{
			out = outputSignal_f32[i] ; 
			for(j=0 ; j<3000 ; j++) ; 
		}
		if(i==SIG_LEN-1) i=0 ; 
}
void plot(void)
{
	int i , j ; 
	for(i=0;i<SIG_LEN;i++)
		{
			sample = inputSignal_f32_1kHz_15kHz[i] ; 
			//for(j=0 ; j<3000 ; j++) ; 
			out = outputSignal_f32[i] ; 
			for(j=0 ; j<8000 ; j++) ; 
		}
		if(i==SIG_LEN-1) i=0 ; 
}

void SysTick_Handler(void)
{
	HAL_IncTick() ; 
	HAL_SYSTICK_IRQHandler() ;
}

