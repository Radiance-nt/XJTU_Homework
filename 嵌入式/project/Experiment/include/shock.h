#ifndef __INCLUDE_SHOCK_H
#define __INCLUDE_SHOCK_H

#include "types.h"
#include "interrupt.h"

void shock_init(void);

int32_t shock_intr_handler(trapframe_t *tf_ptr);

#endif