/*
  tools.h - set of useful constans/includes/etc
  Part of PETPROJ21
  
  Copyright (c) 2021 Aleksandr D. Kazakov | https://github.com/AlexanderDKazakov/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

*/

#include <avr/interrupt.h>
#include <avr/io.h>
#include <IRremote.h>         

const uint16_t TOP             = 65000;
const uint16_t MIN             = 10;
const uint16_t MIN_THRESHOLD   = 5000;
const uint16_t MAX_THRESHOLD   = 64000;
const uint8_t  IR_RECEIVE_PIN  = 7;

ISR (TIMER1_COMPA_vect) { PORTB |= 1 << PORTB2;   }
ISR (TIMER1_COMPB_vect) { PORTB &= ~(1 << PORTB2);}
