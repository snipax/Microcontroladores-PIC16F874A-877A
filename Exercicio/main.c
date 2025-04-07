// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 20000000

void main(void) {
    TRISB = 0b00000100;  // RB2 como entrada, os outros RBs como saída    
    TRISD = 0b00000000; // define todos leds do display como saida
    PORTB = 0b00010000; // liga o RB4 (display)
    int aux; // Previous state para poder segurar o botao
    unsigned char contador = -1;
    
    while(1){
        if (PORTBbits.RB2 == 0 && aux == 1){  // Se botão for pressionado
            if (PORTBbits.RB2 == 0) { // Confirma que o botão está pressionado
                if(PORTBbits.RB0 == 1){
                    PORTBbits.RB0 = 0;
                } else {
                    PORTBbits.RB0 = 1;
                }
                
                contador++;
                if (contador > 9) {
                    contador = 0;
                }
                
                // Mapeamento do display de
                if (contador == 0) {
                PORTD = 0b0111111; // a, b, c, d, e, f
                } else if (contador == 1) {
                PORTD = 0b0000110; // b, c
                } else if (contador == 2) {
                PORTD = 0b1011011; ; // a, b, d, e, g
                } else if (contador == 3) {
                PORTD = 0b1001111; // a, b, c, d, g
                } else if (contador == 4) {
                PORTD = 0b1100110; // b, c, f, g
                } else if (contador == 5) {
                PORTD = 0b1101101; // a, c, d, f, g
                } else if (contador == 6) {
                PORTD = 0b1111101; // a, c, d, e, f, g
                } else if (contador == 7) {
                PORTD = 0b0000111; // a, b, c
                } else if (contador == 8) {
                PORTD = 0b1111111; // a, b, c, d, e, f, g
                } else if (contador == 9) {
                PORTD = 0b1101111; // a, b, c, d, f, g
                }

            }
        }
        aux = PORTBbits.RB2; // define a previous state como o valor atual de RB2
        __delay_ms(100);
    }
}
