#include "lpf.h" 

#define FILTER_TAPS 32 
#define BLOCK 1 

q15_t lpf_coeff[FILTER_TAPS] = 
{
0xFB5C,
0x021C,
0x0219, 
0x024E,  

0x02AC,   
0x0325,    
0x03B0,     
0x0445,      

0x04DC,        
0x056E,         
0x05F7,          
0x0675,           

0x06DB,            
0x072D,             
0x0766,              
0x0782,               

0x0782,                
0x0766,                 
0x072D,                  
0x06DB,                   

0x0675,                    
0x05F7,                     
0x056E,                      
0x04DC,                       

0x0445,
0x03B0,
0x0325,
0x02AC,

0x024E,
0x0219,
0x021C,
0xFB5C,
};

q15_t lpf_state[FILTER_TAPS + BLOCK] ; 

arm_fir_instance_q15 lpf ;

void lpf_init(void)
{
		arm_fir_init_q15(&lpf,FILTER_TAPS,lpf_coeff,lpf_state,BLOCK) ; 
}

q15_t lpfilter(q15_t *input)
{
	 q15_t out;
	 arm_fir_q15(&lpf, input, &out, BLOCK);
	
	return out;
	

	
}
