#include <LPC17xx.h>
#include <stdio.h>
#include"lcd_disp.h"
#define Ref_Vtg 3.300      // Reference voltage (3.3V)
#define Full_Scale 0xFFF   // 12-bit ADC full scale (4095)



int main(void)
{
    unsigned long adc_temp1, adc_temp2;
    unsigned int i;
    float in_vtg1, in_vtg2, in_vdiff, in_adiff;
    unsigned char vtg1[7], vtg2[7], vdiff[7], adiff[7];
    unsigned char Msg3[9] = {"V. diff: "}; 
    unsigned char Msg4[9] = {"D. diff: "}; 

    SystemInit();
    SystemCoreClockUpdate();

    // Power for GPIO block
    LPC_SC->PCONP |= (1 << 15);
    lcd_init();

//adc pin config
    LPC_PINCON->PINSEL3 |= 0x30000000;
    LPC_PINCON->PINSEL3 |= 0xC0000000;

    LPC_SC->PCONP |= (1 << 12);

    SystemCoreClockUpdate();

    lcd_comdata(0x80, 0);
    delay_lcd(800);
    lcd_puts(&Msg3[0]);
    lcd_comdata(0xC0, 0);
    delay_lcd(800);
    lcd_puts(&Msg4[0]);

    while (1)
    {
				LPC_ADC->ADCR = (1 << 4) | (1 << 5) | (1 << 21) | (1 << 16);
        while (!(LPC_ADC->ADDR4 & (1 << 31)) && !(LPC_ADC->ADDR5 & (1 << 31)));

        // read ADC values
        adc_temp1 = LPC_ADC->ADDR4;
        adc_temp1 >>= 4;
        adc_temp1 &= 0xFFF;
        adc_temp2 = LPC_ADC->ADDR5;
        adc_temp2 >>= 4; 
        adc_temp2 &= 0xFFF; 

        // cal the input voltages
        in_vtg1 = (((float)adc_temp1 * (float)Ref_Vtg)) / ((float)Full_Scale);
        in_vtg2 = (((float)adc_temp2 * (float)Ref_Vtg)) / ((float)Full_Scale);
        // calculate abs diff
        in_adiff = (float)adc_temp1 - (float)adc_temp2;
        in_vdiff = (float)in_vtg1 - (float)in_vtg2;
        if (in_vdiff < 0) in_vdiff = -in_vdiff; 
        if (in_adiff < 0) in_adiff = -in_adiff;

        sprintf(vdiff, "%3.2fV", in_vdiff);
        sprintf(adiff, "%03X", (int)in_adiff);

        for (i = 0; i < 2000; i++);
        lcd_comdata(0x89, 0);
        delay_lcd(800);
        lcd_puts(&vdiff[0]);

        lcd_comdata(0xC8, 0);
        delay_lcd(800);
        lcd_puts(&adiff[0]);

        for (i = 0; i < 200000; i++);

				for (i = 0; i < 7; i++) {
            vdiff[i] = adiff[i] = 0;
        }

        adc_temp1 = 0;
        in_vtg1 = 0;
        adc_temp2 = 0;
        in_vtg2 = 0;
    }
}
