.extern intrrupt_dispatcher

.global trap_entry
trap_entry:
    # 切换栈指针, 注意trapframe构建在哪个栈中, 需要进行切换
    # 保存所有寄存器
    mv r0, r1
    # 注意传参
    call intrrupt_dispatcher
    j trap_exit



.global trap_exit
trap_exit:
    mv r1, r0
    # 恢复所有寄存器
    ret