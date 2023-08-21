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

#include "interface.h"

void AumentarMinuto(uint8_t entrada[6]) {
    if (entrada[3] < 9) {
        entrada[3]++;
    } else if (entrada[3] == 9) {
        if (entrada[2] < 5) {
            entrada[2]++;
        } else if (entrada[2] == 5) {
            entrada[2] = 0;
        }
        entrada[3] = 0;
    }
    return;
}

void AumentarHora(uint8_t entrada[6]) {
    if (entrada[0] < 2) {
        if (entrada[1] < 9) {
            entrada[1]++;
        } else if (entrada[1] == 9) {
            entrada[0]++;
            entrada[1] = 0;
        }
    } else if (entrada[0] == 2) {
        if (entrada[1] < 3) {
            entrada[1]++;
        } else if (entrada[1] == 3) {
            entrada[0] = 0;
            entrada[1] = 0;
        }
    }
    return;
}

void DisminuirMinuto(uint8_t entrada[6]) {
    if (entrada[3] > 0) {
        entrada[3]--;
    } else if (entrada[3] == 0) {
        if (entrada[2] > 0) {
            entrada[2]--;
        } else if (entrada[2] == 0) {
            entrada[2] = 5;
        }
        entrada[3] = 9;
    }
    return;
}

void DisminuirHora(uint8_t entrada[6]) {
    if (entrada[0] > 0) {
        if (entrada[1] > 0) {
            entrada[1]--;
        } else if (entrada[1] == 0) {
            entrada[0]--;
            entrada[1] = 9;
        }
    } else if (entrada[0] == 0) {
        if (entrada[1] > 0) {
            entrada[1]--;
        } else if (entrada[1] == 0) {
            entrada[0] = 2;
            entrada[1] = 3;
        }
    }
    return;
}

void PuntoModo(placa_t board, clock_t reloj, modo_t modo) {
    switch (modo) {
    case SIN_CONFIGURAR:
        DisplayPunto(board->display, 1);
        break;
    case MOSTRANDO_HORA:
        DisplayPunto(board->display, 1);
        if (AlarmaGetState(reloj)) {
            DisplayPunto(board->display, 3);
        }
        if (AlarmaActivar(reloj)) {
            DisplayPunto(board->display, 0);
        }
        break;
    case ACTUAL_AJUSTANDO_MINUTOS:
        DisplayPunto(board->display, 2);
        DisplayPunto(board->display, 3);
        break;
    case ACTUAL_AJUSTANDO_HORAS:
        DisplayPunto(board->display, 0);
        DisplayPunto(board->display, 1);
        break;
    case ALARMA_AJUSTANDO_MINUTOS:

        DisplayPunto(board->display, 0);
        DisplayPunto(board->display, 1);
        DisplayPunto(board->display, 2);
        DisplayPunto(board->display, 3);
        break;
    case ALARMA_AJUSTANDO_HORAS:
        DisplayPunto(board->display, 0);
        DisplayPunto(board->display, 1);
        DisplayPunto(board->display, 2);
        DisplayPunto(board->display, 3);
        break;
    default:
        break;
    }
}