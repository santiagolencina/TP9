/************************************************************************************************
Copyright (c) 2023, Lencina Martínez Luis Santiago

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

#include "pantalla.h"
#include <string.h>


#define BORRAR_MEMORIA_VIDEO memset(display->memory, 0, sizeof(display->memory))

struct display_s {
    uint8_t digits;
    uint8_t active_digit;
    uint8_t memory[DISPLAY_MAX_DIGITS];
    struct display_driver_s driver[1];

    uint8_t flashing_desde;
    uint8_t flashing_hasta;
    uint16_t flashing_frecuencia;
    uint16_t flashing_contador;
};


static const uint8_t IMAGES[] = {
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_C | SEGMENTO_D | SEGMENTO_E | SEGMENTO_F,              
    SEGMENTO_B | SEGMENTO_C,                                                                  
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_D | SEGMENTO_E | SEGMENTO_G,                           
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_C | SEGMENTO_D | SEGMENTO_G,                           
    SEGMENTO_B | SEGMENTO_C | SEGMENTO_F | SEGMENTO_G,                                        
    SEGMENTO_A | SEGMENTO_C | SEGMENTO_D | SEGMENTO_F | SEGMENTO_G,                           
    SEGMENTO_A | SEGMENTO_C | SEGMENTO_D | SEGMENTO_E | SEGMENTO_F | SEGMENTO_G,              
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_C,                                                     
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_C | SEGMENTO_D | SEGMENTO_E | SEGMENTO_F | SEGMENTO_G, 
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_C | SEGMENTO_F | SEGMENTO_G,                           
};




static display_t DisplayAllocate(void);


display_t DisplayAllocate(void) {
    static struct display_s instances[1] = {0};

    return &instances[0];
}


display_t DisplayCreate(uint8_t digits, display_driver_t driver) {
    display_t display = DisplayAllocate();

    if (display) {
        display->digits = digits;
        display->active_digit = digits - 1;

        display->flashing_desde = 0;
        display->flashing_hasta = 0;
        display->flashing_frecuencia = 0;
        display->flashing_contador = 0;

        memcpy(display->driver, driver, sizeof(display->driver));
        BORRAR_MEMORIA_VIDEO;
        display->driver->ScreenTurnOff();
    }
    return display;
}

void DisplayWriteBCD(display_t display, uint8_t * number, uint8_t size) {
    BORRAR_MEMORIA_VIDEO;
    for (int index = 0; index < size; index++) {
        if (index >= display->digits)
            break;
        display->memory[index] = IMAGES[number[index]];
    }
}

void DisplayRefresh(display_t display) {

    uint8_t segments;

    display->driver->ScreenTurnOff();
    display->active_digit = (display->active_digit + 1) % display->digits;

    segments = display->memory[display->active_digit];
    if (display->flashing_frecuencia) {
        if (display->active_digit == 0) {
            display->flashing_contador = (display->flashing_contador + 1) % display->flashing_frecuencia;
        }
        if ((display->active_digit >= display->flashing_desde) && (display->active_digit <= display->flashing_hasta)) {
            if (display->flashing_contador > (display->flashing_frecuencia / 2)) {
                segments = 0;
            }
        }
    }

    display->driver->SegmentsTurnOn(segments);
    display->driver->DigitTurnOn(display->active_digit);
}

void DisplayFlashDigit(display_t display, uint8_t desde, uint8_t hasta, uint16_t frecuencia) {
    display->flashing_contador = 0;
    display->flashing_frecuencia = frecuencia;
    display->flashing_desde = desde;
    display->flashing_hasta = hasta;
}

void DisplayPunto(display_t display, uint8_t posicion) {
    display->memory[posicion] ^= (1 << 7);
}