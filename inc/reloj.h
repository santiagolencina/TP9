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
#ifndef RELOJ_H
#define RELOJ_H


#include "define.h"
#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct clock_s * clock_t;

void AumentarTick(clock_t reloj);
clock_t ClockCreate(uint32_t ticks_por_segundos);
bool ClockSetTime(clock_t reloj, const uint8_t * hora, uint32_t size);
bool ClockGetTime(clock_t reloj, uint8_t * hora, uint32_t size);
bool ClockGetTimeState(clock_t reloj);
void ActualizarHora(clock_t reloj);
bool ClockSetAlarm(clock_t reloj, const uint8_t * hora, uint32_t size);
bool ClockGetAlarm(clock_t reloj, uint8_t * hora, uint32_t size);
bool AlarmaOnOf(clock_t reloj, bool estado_requerido);
bool AlarmaGetState(clock_t reloj);
bool AlarmaRest(clock_t reloj, uint8_t tiempo_muerto);
bool AlarmaActivar(clock_t reloj);
bool AlarmaPosponer(clock_t reloj);


#ifdef __cplusplus
}
#endif


#endif