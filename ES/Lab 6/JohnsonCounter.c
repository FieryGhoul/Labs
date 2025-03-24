#include<LPC17xx.h>

unsigned i,j;
unsigned long LED=0x00000010;

int main(void){
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &= 0xFF0000FF; //configure ports p0.4 - p0.11 for GPIO ports
	LPC_GPIO0->FIODIR |= 0x00000FF0;   //configure ports p0.4 to p0.11 for output port
						
	while(1){
		LED=0x00000010;
		for(i=1;i<9;i++){
			LPC_GPIO0->FIOSET = LED; //SET LED value in ports
			for(j=0;j<10000;j++); //delay
			LED<<=1;
		}
		LED=0x00000010;
		for(i=1;i<9;i++){
			LPC_GPIO0->FIOCLR = LED; //CLR LED value in ports
			for(j=0;j<10000;j++); //delay
			LED<<=1;
		}
	}
}
