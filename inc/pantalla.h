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

#ifndef PANTALLA_H
#define PANTALLA_H


#include "define.h"
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifndef DISPLAY_MAX_DIGITS
#define DISPLAY_MAX_DIGITS 8
#endif

#define SEGMENTO_A (1 << 0)
#define SEGMENTO_B (1 << 1)
#define SEGMENTO_C (1 << 2)
#define SEGMENTO_D (1 << 3)
#define SEGMENTO_E (1 << 4)
#define SEGMENTO_F (1 << 5)
#define SEGMENTO_G (1 << 6)
#define SEGMENTO_P (1 << 7)

typedef struct display_s * display_t;
typedef void (*display_screen_off_t)(void);
typedef void (*display_segmentos_on_t)(uint8_t segments);
typedef void (*display_digit_on_t)(uint8_t digit);

typedef struct display_driver_s {
    // struct display_driver_s {
    display_screen_off_t ScreenTurnOff;    //!< Funcion para apagar los segmentos y los digitos
    display_segmentos_on_t SegmentsTurnOn; //!< Funcion para prender determinados segmentos
    display_digit_on_t DigitTurnOn;        //!< Funcion para prender un digito
} const * const display_driver_t;          //!< Puntero al controlador de pantalla

display_t DisplayCreate(uint8_t digits, display_driver_t driver);
void DisplayWriteBCD(display_t display, uint8_t * number, uint8_t size);
void DisplayRefresh(display_t display);
void DisplayFlashDigit(display_t display, uint8_t desde, uint8_t hasta, uint16_t frecuencia);
void DisplayPunto(display_t display, uint8_t posicion);

#ifdef __cplusplus
}
#endif


#endif