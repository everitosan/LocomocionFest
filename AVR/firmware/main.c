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
  //ADMUX |= 1 << ADLAR; //Left ajust of ADC

  ADCSRA |= 1 << ADEN; //Turn On convertion
  ADCSRA |= 1 << ADPS2; //set prescale to 16
  ADCSRA |= 1 << ADIE; //Enable interrupts
}


ISR(ADC_vect) {
  uint8_t thelow = ADCL;
  uint16_t tenBitResult = ADCH <<8 | thelow;


  switch(ADMUX) {
    case 0x40: //0b 0100 0000 => 60
      itoa(tenBitResult, readenValue,10);
      sendData('1');
      ADMUX = 0x42;
        break;


    case 0x42: //0b 0100 0010 => 62
      itoa(tenBitResult, readenValue,10);
      sendData('2');
      ADMUX = 0x40;
      break;

    default:  
      break;
  }

  
  _delay_ms(8);
  ADCSRA |= 1 << ADSC;

}
