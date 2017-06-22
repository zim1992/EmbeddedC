#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/delay.h>
#include <stdio.h>
#include <string.h>
float time = 0;
float oldTime = 0;
int degree = 90;
int powerState = 0;

void setup()
{
  cli();
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = ((111524));// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();
  pinMode(7, OUTPUT);
//  digitalWrite(7,LOW);
  Serial.begin(9600);
}
ISR(TIMER1_COMPA_vect)
{
  switch(powerState){
   case 0:digitalWrite(7, LOW);
         powerState = 1;
//         Serial.println(powerState);
         break;
   case 1:digitalWrite(7,HIGH);
          powerState = 0;
//          Serial.println(powerState);
         break;
   default:Serial.println("ERROR:Undefined state for the LED");
         break;
}
}
void loop()
{
  int a =4;
  Serial.println(powerState);
}
