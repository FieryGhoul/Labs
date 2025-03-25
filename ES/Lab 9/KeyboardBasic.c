#include <LPC17xx.h>

// Function Declarations
void delay_lcd(int);
void clear_ports(void);
void lcd_puts(char*);
void lcd_comdata(int, int);
void write(int, int);
void lcd_init(void);
void scan(void);

unsigned char Msg1[13] = "KEY PRESSED=";
unsigned char row, var, flag, key;
unsigned long int i, varl, temp, templ, temp2, temp3;

unsigned char SCAN_CODE[16] = {0x11,0x21,0x41,0x81,
                                0x12,0x22,0x42,0x82,
                                0x14,0x24,0x44,0x84,
                                0x18,0x28,0x48,0x88};

unsigned char ASCII_CODE[16] = {'0','1','2','3',
                                '4','5','6','7',
                                '8','9','A','B',
                                'C','D','E','F'};

int main(void) {
    SystemInit();
    SystemCoreClockUpdate();

    // Configure GPIO
    LPC_GPIO2->FIODIR |= 0x00003C00; // Rows P2.10 - P2.13 as output
    LPC_GPIO1->FIODIR &= 0xF87FFFFF; // Columns P1.23 - P1.26 as input
    LPC_GPIO0->FIODIR |= (0x0F << 23) | (1 << 27) | (1 << 28); // LCD Control pins

    clear_ports();
    delay_lcd(3200);
    lcd_init();
    lcd_comdata(0x80, 0); // Move cursor to first line of LCD
    delay_lcd(800);
    lcd_puts((char*)Msg1); // Display "KEY PRESSED="

    while (1) {
        char displayKey[2]; // Declare variable at the start

        while (1) {
            for (row = 1; row <= 4; row++) {
                if (row == 1) varl = 0x00000400;
                else if (row == 2) varl = 0x00000800;
                else if (row == 3) varl = 0x00001000;
                else if (row == 4) varl = 0x00002000;

                temp = varl;
                LPC_GPIO2->FIOCLR = 0x00003C00; // Clear previous row states
                LPC_GPIO2->FIOSET = varl; // Enable current row

                flag = 0;
                scan(); 

                if (flag == 1) break;
            }
            if (flag == 1) break;
        }

        for (i = 0; i < 16; i++) {
            if (key == SCAN_CODE[i]) {
                key = ASCII_CODE[i]; // Convert scan code to ASCII
                break;
            }
        }

        lcd_comdata(0xC0, 0); // Move cursor to second line
        delay_lcd(800);

        displayKey[0] = key;  // Assign key value
        displayKey[1] = '\0'; // Null-terminate string

        lcd_puts(displayKey); // Display pressed key
    }
}

// Keypad scanning function
void scan(void) {
    temp3 = LPC_GPIO1->FIOPIN;
    temp3 &= 0x07800000; // Mask relevant column bits

    if (temp3 != 0x00000000) {
        flag = 1; // A key is pressed
        temp3 >>= 19; // Shift column bits to correct position
        temp >>= 10; // Shift row bits
        key = temp3 | temp; // Combine row and column to get scan code
    }
}

// LCD Functions

void delay_lcd(int r1){
    unsigned int r;
    for(r = 0; r < r1; r++);
    return;
}

void clear_ports(void){    
    LPC_GPIO0->FIOCLR = 0x0F << 23;    // Data lines clear
    LPC_GPIO0->FIOCLR = 1 << 27;       // RS line clear
    LPC_GPIO0->FIOCLR = 1 << 28;       // Enable line clear
    return;
}

void lcd_puts(char* string){
    unsigned int i = 0;
    unsigned int temp3;
    while (string[i] != '\0') {
        temp3 = string[i];
        lcd_comdata(temp3, 1);
        i++;
        if (i == 16) lcd_comdata(0xC0, 0); // Move to second line after 16 characters
    }
    return;
}

void lcd_comdata(int temp1, int type){
    int temp2 = temp1 & 0xF0;
    temp2 = temp2 << 19; 
    write(temp2, type);

    temp2 = temp1 & 0x0F;
    temp2 = temp2 << 23;
    write(temp2, type);

    delay_lcd(10000);
    return;
}

void write(int temp2, int type){
    clear_ports();
    LPC_GPIO0->FIOPIN = temp2;

    if (type == 0)
        LPC_GPIO0->FIOCLR = 1 << 27; // Command mode
    else
        LPC_GPIO0->FIOSET = 1 << 27; // Data mode

    LPC_GPIO0->FIOSET = 1 << 28;
    delay_lcd(10000);
    LPC_GPIO0->FIOCLR = 1 << 28;
    return;
}

void lcd_init() {
    LPC_PINCON->PINSEL1 &= 0xFC003FFF; // P0.23 to P0.28 as GPIO
    LPC_GPIO0->FIODIR |= 0x0F << 23 | 1 << 27 | 1 << 28; // Set pins as output

    clear_ports();
    delay_lcd(3200);
    lcd_comdata(0x33, 0); // Initialize LCD in 8-bit mode
    delay_lcd(30000); 
    lcd_comdata(0x32, 0); // Set to 4-bit mode
    delay_lcd(30000);
    lcd_comdata(0x28, 0); // Function set
    delay_lcd(30000);
    lcd_comdata(0x0C, 0); // Display on, cursor off
    delay_lcd(800);
    lcd_comdata(0x06, 0); // Entry mode set, increment cursor right
    delay_lcd(800);
    lcd_comdata(0x01, 0); // Clear display
    delay_lcd(10000);
    return;
}
