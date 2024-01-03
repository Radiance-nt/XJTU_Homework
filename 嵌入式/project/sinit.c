/**
 * @file sinit.c
 * @author Shihong Wang (jack4shihong@gmail.com)
 * @brief `sinit.c`对`SBI`进行初始化
 * @version 0.1
 * @date 2023-04-14
 * 
 * @copyright Copyright Shihong Wang (c) 2023 with GNU Public License V3.0
 */

#include "sbi/sinit.h"
#include "sbi/strap.h"
#include "sbi/secall.h"
#include "sbi/sstdio.h"


void sinit_all(void){
    // 初始化 SBI 异常/中断处理模块
    bprintf("=> strap_init\n");
    strap_init();
    // 初始化 SBI Ecall 异常处理模块
    bprintf("=> ecall_init\n");
    ecall_init();
}