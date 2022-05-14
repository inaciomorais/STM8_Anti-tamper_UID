﻿// A. Inácio Morais - 05/2022 
// anderson.morais@protonmail.com - Brazil
//
// SDCC and STM8FLASH - SMT8S103F3 - HSI 16 MHz
// 

#define CLK_CKDIVR *(unsigned char*)0x50C6

#define PB_ODR *(unsigned char*)0x5005
#define PB_IDR *(unsigned char*)0x5006
#define PB_DDR *(unsigned char*)0x5007
#define PB_CR1 *(unsigned char*)0x5008
#define PB_CR2 *(unsigned char*)0x5009

#define TIM2_CR1 *(unsigned char*)0x5300
	#define CEN 0
#define TIM2_SR1 *(unsigned char*)0x5304
	#define UIF 0
#define TIM2_PSCR *(unsigned char*)0x530E
#define TIM2_ARRH *(unsigned char*)0x530F
#define TIM2_ARRL *(unsigned char*)0x5310

#define U_ID1 *(unsigned char*)0x4865
#define U_ID2 *(unsigned char*)0x4866
#define U_ID3 *(unsigned char*)0x4867
#define U_ID4 *(unsigned char*)0x4868
#define U_ID5 *(unsigned char*)0x4869
#define U_ID6 *(unsigned char*)0x486A
#define U_ID7 *(unsigned char*)0x486B
#define U_ID8 *(unsigned char*)0x486C
#define U_ID9 *(unsigned char*)0x486D
#define U_ID10 *(unsigned char*)0x486E
#define U_ID11 *(unsigned char*)0x486F
#define U_ID12 *(unsigned char*)0x4870


void delay_us(unsigned int us) 		// Reliable for delay equal to or greater than 5us only | fMASTER(HSI) = 16 MHz | SDCC
{
	unsigned char byte_msb = (us >> 8), byte_lsb = us & 0x00FF;

	TIM2_SR1 &= ~(1 << UIF); 	// Clear the update event flag
	TIM2_PSCR = 0x04; 		// 1000 MHz (16 MHz/16 -> 1 us)
	TIM2_ARRH = byte_msb;
	TIM2_ARRL = byte_lsb;
	TIM2_CR1 |= (1 << CEN);		// Enabling timer 2 counter
	while (!(TIM2_SR1 & (1 << UIF)));	// Loop until the update event flag is set
}

void delay_ms(unsigned int ms) 		// fMASTER(HSI) = 16 MHz | SDCC
{
	unsigned int i;
	for (i=0;i<ms;i++) {
		delay_us(1000);
	}
}

int main()
{
	CLK_CKDIVR = 0x00;
		  
	PB_DDR = 0x20;
	PB_CR1 = 0x20;
 
	delay_ms(100);
	
	while (U_ID1 != 0x00 || U_ID2 != 0x00 || U_ID3 != 0x00 || U_ID4 != 0x00 || U_ID5 != 0x00 || U_ID6 != 0x00 || U_ID7 != 0x00 || U_ID8 != 0x00 || U_ID9 != 0x00 || U_ID10 != 0x00 || U_ID11 != 0x00 || U_ID12 != 0x00);	

	while(1)
	{
		PB_ODR ^= 0x20;
		delay_ms(1000);
	}
}


