#ifndef __INCLUDE_LCD_H
#define __INCLIDE_LDC_H

#include "types.h"

void lcd_init(void);

void lcd_set_cursor(int pos);

void lcd_put(const char ch);

void lcd_puts(const char *msg);

#endif