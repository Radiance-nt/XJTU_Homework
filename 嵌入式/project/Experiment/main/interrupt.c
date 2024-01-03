#include "interrupt.h"


void interrupt_init(void){

}


void intrrupt_dispatcher(trapframe_t *tf_ptr){
    intr_no_t intr_no = tf_ptr->r0;

    tf_ptr->r1 = intr_handlers[intr_no](tf_ptr);
}


void register_intr_handler(uint32_t intr_no, intr_handler_t intr_handler, const char* intr_msg){

}