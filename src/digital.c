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


#include "digital.h"
#include "chip.h"
#include <stdint.h>

struct digital_output_s {
    uint8_t port;   
    uint8_t pin;    
    bool allocated; 
    bool inverted;  
};

struct digital_input_s {
    uint8_t port;    
    uint8_t pin;     
    bool allocated;  
    bool inverted;   
    bool last_state; 
};


digital_output_t DigitalOutputAllocate(void);
digital_input_t DigitalInputAllocate(void);

digital_output_t DigitalOutputAllocate(void) {
    digital_output_t output = NULL;

    static struct digital_output_s instances[OUTPUT_INSTANCES] = {0};

    for (int i = 0; i < OUTPUT_INSTANCES; i++) {
        if (!instances[i].allocated) {
            instances[i].allocated = true;
            output = &instances[i];
            break;
        }
    }
    return output;
}

digital_input_t DigitalInputAllocate(void) {
    digital_input_t input = NULL;

    static struct digital_input_s instancias[INPUT_INSTANCES] = {0};

    for (int i = 0; i < INPUT_INSTANCES; i++) {
        if (!instancias[i].allocated) {
            instancias[i].allocated = true;
            input = &instancias[i];
            break;
        }
    }
    return input;
}

digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin, bool inverted) {
    digital_output_t output = DigitalOutputAllocate();

    if (output) {
        output->port = port;
        output->pin = pin;
        output->inverted = inverted;

        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output->port, output->pin, true);
    }
    return output;
}

void DigitalOutputActivate(digital_output_t output) {
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, true);

    return;
}

void DigitalOutputDesactivate(digital_output_t output) {
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);

    return;
}

void DigitalOutputToggle(digital_output_t output) {
    Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, output->port, output->pin);

    return;
}

digital_input_t DigitalInputCreate(uint8_t port, uint8_t pin, bool inverted) {
    digital_input_t input = DigitalInputAllocate();

    if (input) {
        input->port = port;
        input->pin = pin;
        input->inverted = inverted;

        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, input->port, input->pin, false);
    }

    return input;
}

bool DigitalInputGetState(digital_input_t input) {
    return (!input->inverted ^ Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, input->port, input->pin));
}

bool DigitalInputHasChange(digital_input_t input) {
    bool state = DigitalInputGetState(input);
    bool result = (state != input->last_state);

    input->last_state = state;

    return result;
}

bool DigitalInputHasActivate(digital_input_t input) {
    bool state = DigitalInputGetState(input);
    bool result = (state && !input->last_state);

    input->last_state = state;

    return result;
}

bool DigitalInputHasDesactivate(digital_input_t input) {
    bool state = DigitalInputGetState(input);
    bool result = (!state && input->last_state);

    input->last_state = state;

    return result;
}