#include<LPC17xx.h>
unsigned int i,j;
unsigned long LED=0x10;

int main(void){
	
	SystemInit();
	SystemCoreClockUpdate();
	
  LPC_PINCON->PINSEL0=0xFF0000FF;  //port p0.4 to p0.11
  LPC_PINCON->PINSEL4=0xFCFFFFFF;  //port p2.12

  LPC_GPIO0->FIODIR |= 0x00000FF0;  //gpio output
  LPC_GPIO2->FIODIR &= ~(1<<12);    //gpio input

  while(1){
    if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){        //checking if sw2 is clicked
      LPC_GPIO0->FIOCLR=LED;      //clearing port
      for(j=0;j<10000;j++);      //delay
      LED -= 0x10;                //down counter
      if(LED==0x10)               //if goes at 0x10 start again from 0xFF0
          LED=0xFF0;  
    }
    else{
      LPC_GPIO0->FIOCLR=LED;      //clearing port
      for(j=0;j<10000;j++);      //delay
      LED += 0x10;                //up counter
      if(LED==(0x10<<8))          //if crosses 256 go back to 1
          LED=0x10;
    }
    LPC_GPIO0->FIOSET=LED;                          //Set LED value on
    for(j=0;j<10000;j++);                          //delay
  }
}
