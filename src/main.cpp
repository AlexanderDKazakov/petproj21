/*
  main.cpp - Main entry to {PETPROJ21}
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

#include <cooler.h>

int main(void)
{
    Cooler c;                              // Cooler on port PB2.
    IrReceiver.begin(IR_RECEIVE_PIN);      // IRReceiver initialization
    c.init();                              // Cooler initialization
    sei();                                 // Enable Global Interrupts
    while (1)
    {
      if (IrReceiver.decode())
      {
        if (IrReceiver.decodedIRData.command)
        {
          c.call(IrReceiver.decodedIRData.command);
        }
        IrReceiver.resume();
      }
    }
}
