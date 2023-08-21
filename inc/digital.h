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

#ifndef DIGITAL_H
#define DIGITAL_H


#include "define.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OUTPUT_INSTANCES
#define OUTPUT_INSTANCES 4
#endif

#ifndef INPUT_INSTANCES
#define INPUT_INSTANCES 4
#endif


typedef struct digital_output_s * digital_output_t;
typedef struct digital_input_s * digital_input_t;


digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin, bool inverted);
void DigitalOutputActivate(digital_output_t output);
void DigitalOutputDesactivate(digital_output_t output);
void DigitalOutputToggle(digital_output_t output);
digital_input_t DigitalInputCreate(uint8_t port, uint8_t pin, bool inverted);
bool DigitalInputGetState(digital_input_t input);
bool DigitalInputHasChange(digital_input_t input);
bool DigitalInputHasActivate(digital_input_t input);
bool DigitalInputHasDesactivate(digital_input_t input);

#ifdef __cplusplus
}
#endif


#endif