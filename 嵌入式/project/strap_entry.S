#include "sbi/stfoffset.h"

/**
 * @brief `strap_enter`是`SBI`的陷入入口函数, C语言描述为`void strap_enter(void)`
 * 
 * @note `strap_enter`函数的作用:
 *  1. 保存现场: 将通用寄存器和一些csr寄存器保存到陷入栈中
 *  2. 读取中断/异常号, 以作为参数调用`strap_dispatcher`函数处理异常
 * 
 * @note 
 *  1. `strap_enter`的地址将保存到`mtvec`寄存器中, 具体由`strap.c`的`strap_init`函数实现
 *  2. `mtvec`的直接模式`mode = 0`要求`strap_enter`的地址要4字节对齐, 这里是8字节对齐
 *  3. 在`strap_init`将`mtvec`的中断向量值设置为`strap_enter`的地址后, 未来发生了异常就会进入到该`strap_init`函数中运行
 *  4. 但是`RISC-V`的异常默认是在`M模式`下处理的, 异常处理涉及到的寄存器只能在`M模式`下设置和访问;
 *     如果`S模式`想要使用某个功能，只能先回到`M模式`然后再进行相应的设置;
 *     因此`RISC-V`提供了`ecall`指令, 执行`ecall`指令首先从`S模式`切换到`M模式`, 而后触发`EC=8/9/11`的异常;
 *     从而实现了`S模式`调用`M模式`提供的功能
 */
.align 3
.global strap_enter
strap_enter:
    # 从mscratch获取M模式的sp，把先前模式(S模式)的sp保存到mscratch寄存器中, 即交换M模式的栈顶指针和先前模式的栈顶指针
	# 此后, sp寄存器保存的是M模式的栈顶指针
	csrrw sp, mscratch, sp

    # 栈顶指针向上移动一个trap frame
	addi sp, sp, -(STF_SIZE)

    # 存储trap frame具体的值, 具体先保存通用寄存器, 然后保存 csr 寄存器
	sd x1,  STF_RA(sp)
	sd x3,  STF_GP(sp)
	sd x5,  STF_T0(sp)
	sd x6,  STF_T1(sp)
	sd x7,  STF_T2(sp)
	sd x8,  STF_S0(sp)
	sd x9,  STF_S1(sp)
	sd x10, STF_A0(sp)
	sd x11, STF_A1(sp)
	sd x12, STF_A2(sp)
	sd x13, STF_A3(sp)
	sd x14, STF_A4(sp)
	sd x15, STF_A5(sp)
	sd x16, STF_A6(sp)
	sd x17, STF_A7(sp)
	sd x18, STF_S2(sp)
	sd x19, STF_S3(sp)
	sd x20, STF_S4(sp)
	sd x21, STF_S5(sp)
	sd x22, STF_S6(sp)
	sd x23, STF_S7(sp)
	sd x24, STF_S8(sp)
	sd x25, STF_S9(sp)
	sd x26, STF_S10(sp)
	sd x27, STF_S11(sp)
	sd x28, STF_T3(sp)
	sd x29, STF_T4(sp)
	sd x30, STF_T5(sp)
	sd x31, STF_T6(sp)

    # 保存csr寄存器:  mepc 寄存器
	csrr t0, mepc
	sd t0, STF_MEPC(sp)

    # 保存csr寄存器:  mstatus 寄存器
	csrr t0, mstatus
	sd t0, STF_MSTATUS(sp)

	/*
	 * 这里有两个目的:
	 *  1. 保存S模式的SP保存到 sbi_trap_regs->sp
	 *  2. 把M模式的SP保存到mscratch, 以便下次陷入到M模式时候可以得到SP
	 */
    # 让t0指向M模式的栈底部, 注意此时sp指向的还是M模式的栈顶指针
	addi t0, sp, STF_SIZE
    # 此时的sp寄存器保存的是M模式的栈顶指针, mscratch保存的是S模式的SP
	# 下面这句话把S模式的栈顶指针保存到t0寄存器中, 而后把M模式的栈顶指针(t0中的而非sp中的)保存到mscratch寄存器中
	csrrw   t0, mscratch, t0
    # 然后把S模式的栈顶指针保存到陷入帧中
	sd t0, STF_SP(sp)

    # 跳转到strap.c的strap_dispatcher函数处理不同的异常/中断
    # RISC-V的传参方式, 前几个参数存入argument 0~7 寄存器, 这里把M模式SP, 即strapframe_t给strap_dispatcher函数
	mv a0, sp
	call strap_dispatcher
    j strap_exit



/**
 * @brief `strap_exit`是`SBI`的陷入入口函数, C语言描述为`void strap_exit(void)`
 * 
 * @note `strap_exit`函数的作用:
 *  1. 恢复现场: 将`strap_enter`中得到的到陷入栈中的通用寄存器和一些csr寄存器的值加载到对应的寄存器中
 */
.global strap_exit
strap_exit:
	/* save context*/
	ld t0, STF_MSTATUS(sp)
	csrw mstatus, t0

	ld t0, STF_MEPC(sp)
	csrw mepc, t0

	ld x1,  STF_RA(sp)
	ld x3,  STF_GP(sp)
	ld x5,  STF_T0(sp)
	ld x6,  STF_T1(sp)
	ld x7,  STF_T2(sp)
	ld x8,  STF_S0(sp)
	ld x9,  STF_S1(sp)
	ld x10, STF_A0(sp)
	ld x11, STF_A1(sp)
	ld x12, STF_A2(sp)
	ld x13, STF_A3(sp)
	ld x14, STF_A4(sp)
	ld x15, STF_A5(sp)
	ld x16, STF_A6(sp)
	ld x17, STF_A7(sp)
	ld x18, STF_S2(sp)
	ld x19, STF_S3(sp)
	ld x20, STF_S4(sp)
	ld x21, STF_S5(sp)
	ld x22, STF_S6(sp)
	ld x23, STF_S7(sp)
	ld x24, STF_S8(sp)
	ld x25, STF_S9(sp)
	ld x26, STF_S10(sp)
	ld x27, STF_S11(sp)
	ld x28, STF_T3(sp)
	ld x29, STF_T4(sp)
	ld x30, STF_T5(sp)
	ld x31, STF_T6(sp)

	ld sp,  STF_SP(sp)
	mret
