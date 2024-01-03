#ifndef __INCLUDE_ETHER_H
#define __INCLUDE_ETHER_H

#include "types.h"
#include "interrupt.h"

void ether_init(void);

int32_t ether_intr_handler(trapframe_t *tf_ptr);

#endif