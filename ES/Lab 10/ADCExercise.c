#include <lpc17xx.h>
#include <stdio.h>
#include "lcd_disp.h"

#define REF 3.300
#define FULL_SCALE 0xFFF

void lcd_printer(unsigned char* a, int screen_pos) {
	lcd_comdata(screen_pos, 0);
	delay_lcd(800);
	lcd_puts(a);
}

int main(void) {
	unsigned int adc4, adc5, i;
	int diff;
	float vdiff;
	unsigned char vtg[7],ad4[7],ad5[7];
	SystemInit();
	SystemCoreClockUpdate();
	LPC_SC->PCONP |= 1 << 15;
	lcd_init();
	LPC_PINCON->PINSEL3 |= 0xF0000000;
	LPC_SC->PCONP |= 1 << 12;
	SystemCoreClockUpdate();
	while(1) {
		LPC_ADC->ADCR = 1 << 4 | 1 << 21 | 1 << 24;
		while(LPC_ADC->ADDR4 & 0x80000000);
		adc4 = LPC_ADC->ADDR4;
		adc4 >>= 4;
		adc4 &= 0xFFF;
		sprintf((char*) ad4, "%X", adc4);
		LPC_ADC->ADCR = 1 << 5 | 1 << 21 | 1 << 24;
		while (!(LPC_ADC->ADDR5 & 0x80000000));
		adc5 = LPC_ADC->ADDR5;
		adc5 >>= 4;
		adc5 &= 0xFFF;
		diff = adc4 - adc5;
		//diff = diff < 0 ? -diff : diff;
		vdiff = ((float) diff * (float) REF) / ((float) FULL_SCALE);
		sprintf((char*) vtg, "%3.2f", vdiff);
		sprintf((char*) ad5, "%X", adc5);
		for (i = 0; i < 2000; i++);
		lcd_printer(&vtg[0], 0x80);
		lcd_printer(&ad4[0], 0xC0);
		lcd_printer(&ad5[0], 0xC9);
		for (i = 0; i < 200000; i++);
		for (i = 0; i < 7; i++)
			vtg[i] = 0x0;
		adc4 = 0;
		adc5 = 0;
		diff = 0;
	}
}
