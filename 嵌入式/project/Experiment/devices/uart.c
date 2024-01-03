#include "uart.h"

void uart_init(void){
    register_intr_handler(INTR_UART, uart_intr_handler, "UART Interrupt");
}


void uart_put(const char ch){

}

void uart_puts(const char *str){

}

int32_t uart_intr_handler(trapframe_t *tf_ptr){

}