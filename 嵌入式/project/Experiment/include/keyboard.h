#ifndef __INCLUDE_KEYBOARD_H
#define __INCLUDE_KEYBOARD_H

#include "types.h"
#include "interrupt.h"

#define KBBUF_MAX 1024

char kb_buf[KBBUF_MAX];

uint32_t kb_buf_pos = 0;

void keyboard_init(void);

int32_t keyboard_intr_handler(trapframe_t *tf_ptr);

#endif