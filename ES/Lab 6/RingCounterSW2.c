#include<LPC17xx.h>
unsigned int i,j;
unsigned long LED=0x10;

int main(void){
  LPC_PINCON->PINSEL0=0xFF0000FF;  //port p0.4 to p0.11
  LPC_PINCON->PINSEL4=0xFCFFFFFF;  //port p2.12

  LPC_GPIO0->FIODIR |= 0x00000FF0;  //gpio output
  LPC_GPIO2->FIODIR &= ~(1<<12);    //gpio input

  LED = 0x10;
  while(1){
    if((LPC_GPIO1->FIOPIN & (1<<12)) == 0){        //checking if sw2 is clicked
      LPC_GPIO0->FIOCLR=LED;                       //clear current led ports
      for(j=0;j<10000;j++);
      LED<<=1;                                     //shift left
      if(LED==(0x10<<8)){                          //if p0.11 is lit goes back to pin p0.4                    
        LED=0x10;
      }
    }
    LPC_GPIO0->FIOSET=LED;                          //Set LED value on
    for(j=0;j<10000;j++);                          //delay
  }
}
