#ifndef __INCLUDE_INTERRUPT_H
#define __INCLUDE_INTERRUPT_H

#include "trap.h"
#include "types.h"

void interrupt_init(void);

void intrrupt_dispatcher(trapframe_t *tf_ptr);

#define INTR_MAX_NUM 64

typedef int32_t (*intr_handler_t)(trapframe_t *tf_ptr);

intr_handler_t intr_handlers[INTR_MAX_NUM];

const char *intr_msg[INTR_MAX_NUM];

typedef enum __intr_no_t {
    INTR_UART,
    INTR_SHOCK,
    INTR_ETHER,
    INTR_KEYBD
} intr_no_t;

void register_intr_handler(uint32_t intr_no, intr_handler_t intr_handler, const char* intr_msg);

#endif