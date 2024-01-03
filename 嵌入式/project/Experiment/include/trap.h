#ifndef __INCLUDE_TRAP_H
#define __INCLUDE_TRAP_H

#include "types.h"

typedef struct __trapframe_t {
    ireg_t r0;
    ireg_t r1;
} trapframe_t;

#endif