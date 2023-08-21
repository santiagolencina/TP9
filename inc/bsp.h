/************************************************************************************************
Copyright (c) 2023, Lencina Martinez Luis Santiago

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

#ifndef BSP_H
#define BSP_H

#include "chip.h"
#include "define.h"
#include "digital.h"
#include "pantalla.h"


#ifdef __cplusplus
extern "C" {
#endif


#ifdef CIA
typedef struct placa_s {
    digital_output_t led_azul;
    digital_output_t led_rojo;
    digital_output_t led_amarillo;
    digital_output_t led_verde;

    digital_input_t tecla_1;
    digital_input_t tecla_2;
    digital_input_t tecla_3;
    digital_input_t tecla_4;
} const * const placa_t;
#endif

#ifdef PONCHO
typedef struct placa_s {
    digital_output_t buzzer;

    digital_input_t acept;
    digital_input_t cancel;

    digital_input_t increment;
    digital_input_t decrement;

    digital_input_t set_time;
    digital_input_t set_alarm;

    display_t display;
} placa_s;

typedef struct placa_s * placa_t;

#endif

placa_t BoardCreate(void);
void SisTick_Init(uint16_t ticks);

#ifdef __cplusplus
}
#endif

#endif 