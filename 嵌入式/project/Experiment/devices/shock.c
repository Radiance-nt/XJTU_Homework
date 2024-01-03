#include "shock.h"

void shock_init(void){
    register_intr_handler(INTR_SHOCK, shock_intr_handler, "Shock Sensor Interrupt");
}



int32_t shock_intr_handler(trapframe_t *tf_ptr){

}