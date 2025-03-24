#include<LPC17xx.h>
unsigned i,j;
unsigned long LED = 0x10;
int main(void){
  
  SystemInit();
	SystemCoreClockUpdate();

  LPC_PINCON->PINSEL0 = 0xFF0000FF;
  LPC_GPIO0->FIODIR |= 0x00000FF0;
  while(1){
    LED=0x10;
    for(i=0;i<256;i++){
      LPC_GPIO0->FIOPIN=LED;
      for(j=0;j<100000;j++);
      LED+=0x10;
    }
  }
}
