
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

#include "reloj.h"
#include <string.h>



struct clock_s {

    uint8_t hora_actual[6];
    bool valida;
    uint8_t alarma[6]; 
    bool alarma_on;
    bool alarma_activada;
    uint8_t tiempo_pospuesto;
    uint32_t tick_x_sec;   
    uint32_t ticks_actual;
};


void ComprobarDecenaSegundos(uint8_t * hora, clock_t reloj);
void ComprobarUnidadMinutos(uint8_t * hora, clock_t reloj);
void ComprobarDecenaMinutos(uint8_t * hora, clock_t reloj);
void ComprobarUnidadHora(uint8_t * hora, clock_t reloj);
void ComporbarDescanso(clock_t reloj);
bool HoraValida(const uint8_t * hora);


void ComprobarDecenaSegundos(uint8_t * hora, clock_t reloj) {
    if (hora[4] < 5) {
        hora[4]++;
    } else {
        hora[4] = 0;
        ComprobarUnidadMinutos(hora, reloj);
    }
    return;
}

void ComprobarUnidadMinutos(uint8_t * hora, clock_t reloj) {
    if (hora[3] < 9) {
        hora[3]++;
    } else {
        hora[3] = 0;
        ComprobarDecenaMinutos(hora, reloj);
    }
    ComporbarDescanso(reloj);
    return;
}

void ComprobarDecenaMinutos(uint8_t * hora, clock_t reloj) {
    if (hora[2] < 5) {
        hora[2]++;
    } else {
        hora[2] = 0;
        ComprobarUnidadHora(hora, reloj);
    }
    return;
}

void ComprobarUnidadHora(uint8_t * hora, clock_t reloj) {
    if (hora[0] < 2) {
        if (hora[1] < 9) {
            hora[1]++;
        } else {
            hora[1] = 0;
            hora[0]++;
        }
    } else {
        if (hora[1] < 3) {
            hora[1]++;
        } else {
            hora[1] = 0;
            hora[0] = 0;
        }
    }
    return;
}

void ComporbarDescanso(clock_t reloj) {
    if (reloj->tiempo_pospuesto > 0) {
        reloj->tiempo_pospuesto--;
    }
    return;
}

bool HoraValida(const uint8_t * hora) {
    bool aux = false;

    if (hora[5] <= 9 && hora[4] <= 5 && hora[3] <= 9 && hora[2] <= 5) {
        if (hora[1] <= 9 && hora[0] < 2) {
            aux = true;
        } else if (hora[1] <= 3 && hora[0] == 2) {
            aux = true;
        } else {
            aux = false;
        }
    }

    return aux;
}

void AumentarTick(clock_t reloj) {
    reloj->ticks_actual++;
    return;
}

clock_t ClockCreate(uint32_t ticks_por_segundos) {
    static struct clock_s self[1];
    memset(self, 0, sizeof(self));
    self->tick_x_sec = ticks_por_segundos;
    return self;
}

bool ClockGetTime(clock_t reloj, uint8_t * hora, uint32_t size) {
    memcpy(hora, reloj->hora_actual, size);
    return reloj->valida;
}

bool ClockSetTime(clock_t reloj, const uint8_t * hora, uint32_t size) {
    bool aux = true;

    if (HoraValida(hora)) {
        memcpy(reloj->hora_actual, hora, size);
        reloj->valida = true;
    } else {
        aux = false;
    }
    return reloj->valida && aux;
}

bool ClockGetTimeState(clock_t reloj) {
    return reloj->valida;
}

void ActualizarHora(clock_t reloj) {
    uint8_t hora[6];
    bool aux;

    if (reloj->ticks_actual == reloj->tick_x_sec) {
        (void)ClockGetTime(reloj, hora, sizeof(hora));
        if (hora[5] < 9) {
            hora[5]++;
        } else {
            hora[5] = 0;
            ComprobarDecenaSegundos(hora, reloj);
        }
        aux = reloj->valida;
        (void)ClockSetTime(reloj, hora, sizeof(hora));
        reloj->valida = aux;
        reloj->ticks_actual = 0;
        if (reloj->alarma_on) { 
            (void)AlarmaActivar(reloj);
        }
    }
    return;
}

bool ClockGetAlarm(clock_t reloj, uint8_t * hora, uint32_t size) {
    memcpy(hora, reloj->alarma, size);
    return reloj->alarma_on;
}

bool ClockSetAlarm(clock_t reloj, const uint8_t * hora, uint32_t size) {
    bool aux = true;

    if (HoraValida(hora)) {
        memcpy(reloj->alarma, hora, size);
        reloj->alarma_on = true;
    } else {
        aux = false;
    }

    return reloj->alarma_on && aux;
}

bool AlarmaActivar(clock_t reloj) {
    uint8_t hora[6];
    uint8_t alarma[6];

    memcpy(hora, reloj->hora_actual, 6);
    memcpy(alarma, reloj->alarma, 6);

    if (hora[0] == alarma[0] && hora[1] == alarma[1] && hora[2] == alarma[2] && hora[3] == alarma[3] &&
        hora[4] == alarma[4] && hora[5] == alarma[5] && (reloj->alarma_on)) {
        reloj->alarma_activada = true;
    }

    return (reloj->alarma_activada && !reloj->tiempo_pospuesto);
}

bool AlarmaOnOf(clock_t reloj, bool estado_requerido) {
    reloj->alarma_on = estado_requerido;
    return reloj->alarma_on;
}

bool AlarmaGetState(clock_t reloj) {

    return reloj->alarma_on;
}

bool AlarmaRest(clock_t reloj, uint8_t tiempo_muerto) {
    reloj->tiempo_pospuesto = tiempo_muerto;
    return reloj->tiempo_pospuesto;
}

bool AlarmaPosponer(clock_t reloj) {
    reloj->alarma_activada = false;
    return reloj->alarma_activada;
}