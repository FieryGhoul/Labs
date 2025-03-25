#include<LPC17xx.h>

unsigned int i,dig_count = 0;
unsigned char seven_seg[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; 
unsigned int dig_value[4] = {1,2,3,4};
unsigned int digit_select[4] = {0x1000,0x2000,0x4000,0x8000};  // Control lines for each digit

void delay(void) {
    for (i=0;i<50000;i++);
}

int main(void) {
    SystemInit();
    SystemCoreClockUpdate();

    LPC_PINCON->PINSEL0 &= 0xFF0000FF; // Configure P0.4 to P0.11 as GPIO
    LPC_GPIO0->FIODIR |= 0xFFF0;       // Set P0.4-P0.15 as output

    while (1) {
        for (dig_count=0;dig_count<4;dig_count++) {
            LPC_GPIO0->FIOPIN = (seven_seg[dig_value[dig_count]]<<4) | digit_select[dig_count]; 
            delay();
        }
    }
}
