/* Name: main.c
 * Author: everardo sánchez
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <util/delay.h>


void usartinit();
void enablePushButtonInput();

int main(void)
{
    usartinit();
    enablePushButtonInput();
    while(1) {
        if( PINB & 0x10 ) {
          _delay_ms(200);
          UDR0 = '0';
        }
    }
}

void usartinit() {
  UBRR0 = 6;
  UCSR0B = (1 << TXEN0); //Enables transmiter
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void enablePushButtonInput() {
  DDRB = 0x00;
  PORTB = 0x00;
}
