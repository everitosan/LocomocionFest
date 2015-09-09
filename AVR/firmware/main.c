/* Name: main.c
 * Author: everardo sánchez
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void usartinit();
void ADCinit();
void sendData();

char readenValue[4];

int main(void)
{
    usartinit();
    ADCinit();

    ADCSRA |= 1 << ADSC;
    sei();

    while(1) {
    }
}

void sendData () {
  char i = 0;
  for(i; i<4;i++) {
    _delay_ms(2);
    UDR0 = readenValue[i];
  }
  
  UDR0 = '\n';
}

void usartinit() {
  UBRR0 = 6;
  UCSR0B = (1 << TXEN0); //Enables transmiter
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void ADCinit() {
  ADMUX |= 1 << REFS0; //
  ADMUX |= 1 << ADLAR; //

  ADCSRA |= 1 << ADEN; //Turn On convertion
  ADCSRA |= 1 << ADPS2; //set prescale to 16
  ADCSRA |= 1 << ADIE; //Enable interrupts
}


ISR(ADC_vect) {
  itoa(ADCH, readenValue,10);
  sendData();

  ADCSRA |= 1 << ADSC;

}
