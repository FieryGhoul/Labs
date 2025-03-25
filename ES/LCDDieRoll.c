#include<LPC17xx.h>
#include<stdlib.h>
#include<stdio.h>

void lcd_init(void);
void clear_ports(void);
void lcd_puts(char*);
void lcd_comdata(int,int);
void write(int,int);
void delay_lcd(int);

int main(void){
    int randNum;
    char Msg1[10];
    SystemInit();
    SystemCoreClockUpdate(); 
    LPC_PINCON->PINSEL4 &= 0xF0FFFFFF; // Configure P2.12 and P2.13 as GPIO
    LPC_GPIO2->FIODIR &= ~(1 << 12);   // Configure pin 12 as input

    lcd_init();

    while(1) {
        if ( (LPC_GPIO2->FIOPIN & (1 << 12)) == 0 ) {
            randNum = (rand() % 6) + 1;

            lcd_comdata(0x80, 0); // Move cursor to first position
            delay_lcd(800);

            // Format the message
            sprintf((char*)Msg1, "Die Value: %d", randNum);
            lcd_puts(Msg1);
        }
    }
}

void delay_lcd(int r1){
	unsigned int r;
	for(r=0;r<r1;r++);
	return;
}

void clear_ports(void){	
	LPC_GPIO0->FIOCLR = 0x0F<<23;	//data line clear
	LPC_GPIO0->FIOCLR = 1<<27;		//RS line clear
	LPC_GPIO0->FIOCLR = 1<<28;		//enable line clear
	
	return;
}

void lcd_puts(char* string){
	unsigned int i=0;
	unsigned int temp3;
	while(string[i]!='\0'){
		temp3=string[i];
		lcd_comdata(temp3,1);
		i++;
		if(i==16)	lcd_comdata(0xc0,0);
	}
	return;
}

void lcd_comdata(int temp1,int type){
	int temp2 = temp1 & 0xF0;
	temp2=temp2<<19; 
	write(temp2,type);
	
	temp2 = temp1 & 0x0F;
	temp2=temp2<<23;
	write(temp2,type);
	
	delay_lcd(10000);
	return;
}

void write(int temp2, int type){
	clear_ports();
	LPC_GPIO0->FIOPIN = temp2;
	
	if(type==0)
		LPC_GPIO0->FIOCLR = 1<<27;
	else
		LPC_GPIO0->FIOSET = 1<<27;
		
	LPC_GPIO0->FIOSET=1<<28;
	delay_lcd(10000);
	LPC_GPIO0->FIOCLR=1<<28;
	return;
}

void lcd_init() {

    LPC_PINCON->PINSEL1 &= 0xFC003FFF; //P0.23 to P0.28
    LPC_GPIO0->FIODIR |= 0x0F<<23 | 1<<27 | 1<<28;
 
    clear_ports();
    delay_lcd(3200);
    lcd_comdata(0x33, 0); //8-bit mode
    delay_lcd(30000); 
    lcd_comdata(0x32, 0); //4-bit mode
    delay_lcd(30000);
    lcd_comdata(0x28, 0); //function set
    delay_lcd(30000);
    lcd_comdata(0x0c, 0);//display on cursor off
    delay_lcd(800);
    lcd_comdata(0x06, 0); //entry mode set increment cursor right
    delay_lcd(800);
    lcd_comdata(0x01, 0); //display clear
    delay_lcd(10000);
    return;
}
