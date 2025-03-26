#include<lpc17xx.h>
void clock_wise(void);
void anti_clock_wise(void);
unsigned long int var1, var2;
unsigned int i=0, j=0, k=0;
int main(){
	SystemInit();
	SystemCoreClockUpdate();
	//LPC_PICON->PINSEL0 &=	0xfffff00f;	//p0.4 to p0.7 gpio
	LPC_GPIO0->FIODIR |= 0xf0;					//p0.4 to p0.7 output
	while(1){
		for(j=0; j<50; j++)
			clock_wise();
		for(k=0; k<65000; k++);
		for(j=0; j<50; j++)
			anti_clock_wise();
		for(k=0; k<65000; k++);
	}
}
void clock_wise(void){
	var1=0x00000008;
	for(i=0; i<4; i++){
		var1=var1<<1;
		LPC_GPIO0->FIOPIN = var1;
		for(k=0; k<3000; k++);//for speed
	}
}
void anti_clock_wise(void){
	var1=0x00000100;
	for(i=0; i<4; i++){
		var1=var1>>1;
		LPC_GPIO0->FIOPIN = var1;
		for(k=0; k<3000; k++);//for speed
	}
}
