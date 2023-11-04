// A. Inácio Morais - 05/2022
// anderson.morais@protonmail.com - Brazil 
// Unique ID to device EEPROM 
// 311 bytes | 8 kbytes

/*****************************************************************************************************/
#define CLK_CKDIVR *(unsigned char*)0x50C6
/*****************************************************************************************************/
#define PA_ODR *(unsigned char*)0x5000
#define PA_DDR *(unsigned char*)0x5002
#define PA_CR1 *(unsigned char*)0x5003
/*****************************************************************************************************/
#define TIM2_CR1 *(unsigned char*)0x5300
	#define CEN 0
#define TIM2_SR1 *(unsigned char*)0x5304
	#define UIF 0
#define TIM2_PSCR *(unsigned char*)0x530E
#define TIM2_ARRH *(unsigned char*)0x530F
#define TIM2_ARRL *(unsigned char*)0x5310
/*****************************************************************************************************/
#define FLASH_IAPSR *(unsigned char*)0x505F
	#define EOP 2
	#define DUL 3
#define FLASH_DUKR *(unsigned char*)0x5064

#define _MEM_(mem_addr) (*(volatile unsigned char*)(mem_addr))
/*****************************************************************************************************/
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
/*****************************************************************************************************/

_Bool status = 0;

void delay_us(unsigned int us) 		// For delay equal or greater than 5 us only | fMASTER(HSI) = 16 MHz | SDCC
{
	unsigned char byte_msb = (us >> 8), byte_lsb = us & 0x00FF;

	TIM2_SR1 &= ~(1 << UIF); 		// Clear the update event flag
	TIM2_PSCR = 0x04; 			// 1000 MHz (16 MHz/16 -> 1 us)
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
	
	PA_DDR = 0x08;		// PA1 and PA2 as input mode. PA3 as output mode
	PA_CR1 = 0x0E;		/* PA1 and PA2 as input with pull-up to avoid extra current consumption due to floating. PA3 as push-pull output */
	
	delay_ms(500);
	
	if (status == 0) {
		FLASH_DUKR = 0xAE;
		FLASH_DUKR = 0x56;
		while (!(FLASH_IAPSR & (1 << DUL)));

		_MEM_(0x4000) = U_ID1;
		while (!(FLASH_IAPSR & (1 << EOP)));
		_MEM_(0x4001) = U_ID2;
		while (!(FLASH_IAPSR & (1 << EOP)));
		_MEM_(0x4002) = U_ID3;
		while (!(FLASH_IAPSR & (1 << EOP)));
		_MEM_(0x4003) = U_ID4;
		while (!(FLASH_IAPSR & (1 << EOP)));
		_MEM_(0x4004) = U_ID5;
		while (!(FLASH_IAPSR & (1 << EOP)));
		_MEM_(0x4005) = U_ID6;
		while (!(FLASH_IAPSR & (1 << EOP)));
		_MEM_(0x4006) = U_ID7;
		while (!(FLASH_IAPSR & (1 << EOP)));
		_MEM_(0x4007) = U_ID8;
		while (!(FLASH_IAPSR & (1 << EOP)));
		_MEM_(0x4008) = U_ID9;
		while (!(FLASH_IAPSR & (1 << EOP)));
		_MEM_(0x4009) = U_ID10;
		while (!(FLASH_IAPSR & (1 << EOP)));
		_MEM_(0x400A) = U_ID11;
		while (!(FLASH_IAPSR & (1 << EOP)));
		_MEM_(0x400B) = U_ID12;
		while (!(FLASH_IAPSR & (1 << EOP)));
		
		FLASH_IAPSR &= ~(1<< DUL);
		
		status = 1;
	}
		
	while(1)
	{
		PA_ODR ^= (1 << 3);
		delay_ms(250);		
	}
}


