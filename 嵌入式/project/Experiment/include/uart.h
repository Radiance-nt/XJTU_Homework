#ifndef __INCLUDE_UART_H
#define __INCLUDE_UART_H

#include "types.h"
#include "interrupt.h"

void uart_init(void);

void uart_put(const char ch);

void uart_puts(const char *str);

int32_t uart_intr_handler(trapframe_t *tf_ptr);

#endif