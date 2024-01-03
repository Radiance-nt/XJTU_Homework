#include "ether.h"

void ether_init(void){
    register_intr_handler(INTR_ETHER, ether_intr_handler, "Ethernet Interrupt");
}

int32_t ether_intr_handler(trapframe_t *tf_ptr){

}