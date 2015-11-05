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
void sendData(char d);

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

void sendData (char d) {

  UDR0 = d; //enviamos el identificador del ADC
  
}

void usartinit() {
  UBRR0 = 6;
  UCSR0B = (1 << TXEN0); //Enables transmiter
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void ADCinit() {
  ADMUX |= 1 << REFS0; //
  //ADMUX |= 1 << ADLAR; //Left ajust of ADC

  ADCSRA |= 1 << ADEN; //Turn On convertion
  ADCSRA |= 1 << ADPS2; //set prescale to 16
  ADCSRA |= 1 << ADIE; //Enable interrupts
}


ISR(ADC_vect) {
  uint8_t thelow = ADCL;
  uint16_t tenBitResult = ADCH <<8 | thelow;

  char signa;

  switch(ADMUX) {
    case 0x40: //0b 0100 0000 => 60
      itoa(tenBitResult, readenValue,10);
      if (tenBitResult > 767) {
        signa = 0b00110001; //0x31
      }
      else {
        signa = 0b00110000; //0x30
      }
      
        break;

    default:  
      break;
  }

  sendData(signa);

  
  _delay_ms(8);
  ADCSRA |= 1 << ADSC;

}
