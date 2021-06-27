/*
  cooler.h - class for work with cooler on some port[PB2]
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

#include "tools.h"

class Cooler
{
    public:
        Cooler(){}

        void init() 
        {
            // PB2 is output for cooler 
            DDRB  |= (1 << DDB2);   // Set B2 to output
            PORTB |= (1 << PORTB2); // PB2 is output now


            TCCR1A = 0; TCCR1B = 0; TCNT1 = 0; 

            /* configure Timer1 */
            // set up timer with prescaler = 64 and CTC mode /* goes better */
            TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);

            // initialize counter
            TCNT1 = 0;

            // initialize compare values : [Cooler stop]
            OCR1A = TOP;
            OCR1B = MIN;

            // enable compare interrupt
            TIMSK1 |= (1 << OCIE1A);
            TIMSK1 |= (1 << OCIE1B);
        }

        void call(uint16_t IR_command) 
        {
            //off
            if (IR_command == 71) { OCR1A = TOP; OCR1B = MIN;      }
            //1
            if (IR_command == 68) { OCR1A = TOP; OCR1B = TOP / 6;  }
            //2
            if (IR_command == 67) { OCR1A = TOP; OCR1B = TOP / 5;  }
            //3
            if (IR_command == 7)  { OCR1A = TOP; OCR1B = TOP / 4;  }
            //4
            if (IR_command == 9)  { OCR1A = TOP; OCR1B = TOP / 3;  }
            //5
            if (IR_command == 22) { OCR1A = TOP; OCR1B = TOP / 2;  }
            //6
            if (IR_command == 13) { OCR1A = TOP; OCR1B = TOP / 1.5;}
            //7
            if (IR_command == 12) { OCR1A = TOP; OCR1B = TOP / 1.2;}
            //8
            if (IR_command == 94) { OCR1A = MIN; OCR1B = TOP;      }
            //on 
            if (IR_command == 69) { OCR1A = MIN; OCR1B = TOP;      }
            // intensity up
            if (IR_command == 90) {increase_intensity();}
            // intensity down
            if (IR_command == 8)  {decrease_intensity();}
        }

        void reset_mode() { OCR1A = TOP; OCR1B = MIN;}

        void increase_intensity()
        {
            if (OCR1B < MAX_THRESHOLD) {
                OCR1B += _intensityStep;
                OCR1A  = TOP;
            }
        }

        void decrease_intensity()
        {
            if (OCR1B > MIN_THRESHOLD) {
                OCR1B -= _intensityStep;
                OCR1A  = TOP;
            }
        }

    private:
        int16_t _intensityStep = 500;  // quite good choice
};
