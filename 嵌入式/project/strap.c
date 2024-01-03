/**
 * @file strap.c
 * @author Shihong Wang (jack4shihong@gmail.com)
 * @brief `strap.c`是`SBI`的异常/中断管理模块
 * @version 0.1
 * @date 2023-04-16
 * 
 * @copyright Copyright Shihong Wang (c) 2023 with GNU Public License V3.0
 */

#include "uart.h"
#include "string.h"
#include "asm/csr.h"
#include "sbi/strap.h"
#include "sbi/sstdio.h"

// 中断的提示信息
const char *intr_msg[MAX_INTR_EXCP_INFO_NUM] = {
    "User Software Interrupt",
    "Supervisor Software Interrupt",
    "Reserved for Future Standard Use",
    "Machine Software Interrupt",
    "User Timer Interrupt",
    "Supervisor Timer Interrupt",
    "Reserved for Future Standard Use",
    "Machine Timer Interrupt",
    "User External Interrupt",
    "Supervisor External Interrupt",
    "Reserved for Future Standard Use",
    "Machine External Interrupt"
};

// 异常的提示信息
const char *excp_msg[MAX_INTR_EXCP_INFO_NUM] = {
    "Instrution Address Misaligned",
    "Instrution Access Fault",
    "Illegal Instruction",
    "Breakpoint",
    "Load address Misaligned",
    "Load access Fault",
    "Store/AMO address Misaligned",
    "Store/AMO Access Fault",
    "Environment Call from U-Mode",
    "Environment Call from S-Mode",
    "Reserved",
    "Environment Call from M-Mode",
    "Instruction Page Fault",
    "Load Page Fault",
    "Reserved for Future Standard Use",
    "Store/AMO Page Fault"
};

// 中断处理函数表
trap_handler_t intr_handlers[MAX_INTR_EXCP_INFO_NUM];

// 异常处理函数表
trap_handler_t excp_handlers[MAX_INTR_EXCP_INFO_NUM];

void strap_init(void){
    // 设置中断向量地址, 设置为直接模式
    write_csr(mtvec, ((addr_t)strap_enter & (~((addr_t)0b11))));
    // 关闭所有的中断
    write_csr(mie, 0);
    // 为所有的异常和中断注册处理函数
    for (size_t i = 0; i < MAX_INTR_EXCP_INFO_NUM; i++)
        regitser_trap_handler(i, False, NULL, general_trap_handler);
    for (size_t i = 0; i < MAX_INTR_EXCP_INFO_NUM; i++)
        regitser_trap_handler(i, True, NULL, general_trap_handler);
}


void strap_dispatcher(strapframe_t *stf_ptr){
    ireg_t mcause = read_csr(mcause);

    Bool is_interrupt = ((mcause & MCAUSE_INTERRUPT_FLAG) != 0) ? 1 : 0;
    uint64_t trap_code = mcause & ~(MCAUSE_INTERRUPT_FLAG);
    int64_t rtval UNUSED = (is_interrupt ? intr_handlers : excp_handlers)[trap_code](stf_ptr);
}


NO_RETURN int64_t general_trap_handler(strapframe_t *stf_ptr){
    ireg_t mcause = read_csr(mcause);
    Bool is_interrupt = ((mcause & MCAUSE_INTERRUPT_FLAG) != 0) ? 1 : 0;
    uint64_t trap_code = mcause & ~(MCAUSE_INTERRUPT_FLAG);
    const char **msg_source = (is_interrupt ? intr_msg : excp_msg);
    const char *msg = msg_source[trap_code];
    const char *s = is_interrupt ? "Interrupt" : "Exception";
    bprintf("==================================================================\n");
    bprintf("%s Happened, %s ID: %#X, mcause register: %#X\n", s, s, trap_code, mcause);
    bprintf("Detailed Message: %s\n", msg);
    bprintf("No %s handler register for this %s, with ID: %#X\n", s, s, trap_code);
    bprintf("Running %s instead\n", __func__);
    bprintf("Printing Trap Frame:\n");
    print_trapframe(stf_ptr);
    bprintf("Please register handler to avoid hanging!\n");
    bprintf("Hanging HART Here\n");
    while (1);
    UNREACHABLE;
}


void regitser_trap_handler(uint64_t trap_code, Bool interrupt, const char* msg, trap_handler_t trap_func){
    if (msg != NULL)
        strcpy((char*) (interrupt ? intr_msg : excp_msg)[trap_code], msg);
    (interrupt ? intr_handlers : excp_handlers)[trap_code] = trap_func;
}


void print_trapframe(strapframe_t *stf_ptr){
    bprintf("Print Trap Frame at: %#016X\n", (void*)stf_ptr);
    bprintf("mepc: %#016lX                  mstatus : %#016lX\n", stf_ptr->mepc, stf_ptr->mstatus);
	bprintf(" gp : %#016lX tp : %#016lX t0 : %#016lX\n", stf_ptr->gp, stf_ptr->tp, stf_ptr->t0);
	bprintf(" t1 : %#016lX t2 : %#016lX t3 : %#016lX\n", stf_ptr->t1, stf_ptr->t2, stf_ptr->s0);
	bprintf(" s1 : %#016lX a0 : %#016lX a1 : %#016lX\n", stf_ptr->s1, stf_ptr->a0, stf_ptr->a1);
	bprintf(" a2 : %#016lX a3 : %#016lX a4 : %#016lX\n", stf_ptr->a2, stf_ptr->a3, stf_ptr->a4);
	bprintf(" a5 : %#016lX a6 : %#016lX a7 : %#016lX\n", stf_ptr->a5, stf_ptr->a6, stf_ptr->a7);
	bprintf(" s2 : %#016lX s3 : %#016lX s4 : %#016lX\n", stf_ptr->s2, stf_ptr->s3, stf_ptr->s4);
	bprintf(" s5 : %#016lX s6 : %#016lX s7 : %#016lX\n", stf_ptr->s5, stf_ptr->s6, stf_ptr->s7);
	bprintf(" s8 : %#016lX s9 : %#016lX s10: %#016lX\n", stf_ptr->s8, stf_ptr->s9, stf_ptr->s10);
	bprintf(" s11: %#016lX t3 : %#016lX t4 : %#016lX\n", stf_ptr->s11, stf_ptr->t3, stf_ptr->t4);
	bprintf(" t5 : %#016lX t6 : %#016lX sp : %#016lX\n", stf_ptr->t5, stf_ptr->t6, stf_ptr->sp);
	bprintf(" ra : %#016lX\n", stf_ptr->ra);
}