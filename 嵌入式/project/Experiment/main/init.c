#include "sd.h"
#include "rtc.h"
#include "lcd.h"
#include "uart.h"
#include "shock.h"
#include "init.h"


void init_all(){
    // 初始化设备
    sd_init();
    rtc_init();
    lcd_init();
    uart_init();
    shock_init();
}