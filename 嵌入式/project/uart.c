/**
 * @file uart.c
 * @author Shihong Wang (jack4shihong@gmail.com)
 * @brief `uart.c`实现`UART`设备功能
 * @version 0.1
 * @date 2023-04-09
 * 
 * @note `QEMU`默认模拟的`UART`设备处理芯片是`AXI UART 16550`
 * @note 关于`AXI UART 16550`芯片介绍: https://wenku.baidu.com/view/6f7a176048d7c1c708a14521.html?_wkts_=1681021571718
 * @note 关于`AXI UART 16550`相关常量, 参考`AXI UART 16550`编程手册(`Programming Table`): http://byterunner.com/16550.html
 * 
 * @warning 目前使用轮询方式使用`UART`设备, 没有实现中断方式
 * 
 * @copyright Copyright Shihong Wang (c) 2023 with GNU Public License V3.0
 */

#include "uart.h"

void uart_init(void){
    // 参考: https://wenku.baidu.com/view/6f7a176048d7c1c708a14521.html?_wkts_=1681021571718
    // divisor将写入16550的除数寄存器
    uint16_t divisor = (uint16_t) (UART16550_CLOCK / (16 * UART_BAUD_RATE));

    // 目前使用轮询方式, 因此禁止16550的四种中断
    write_8_bits(UART_IER, 0b00000000);

    // 打开DLAB位以设置波特率
    write_8_bits(UART_LCR, 0b10000000);
    write_8_bits(UART_DL_LSB, (uint8_t)(divisor & 0x0011));         // 设置低八位
    write_8_bits(UART_DL_MSB, (uint8_t)((divisor & 0x1100) >> 8));  // 设置高八位

    // 设置传输方式, 数据位长为8位, 不进行奇偶校验, 停止位长1位
    write_8_bits(UART_LCR, 0b00000011);

    // 设置FIFO工作模式, FIFO队列长度设置为14字节, 每次发送/接受数据均清空FIFO
    write_8_bits(UART_FCR, 0b11000111);
}


void uart_put(char chr){
    // 轮询等待缓冲区队列为空
    while ((read_8_bits(UART_LSR) & UART_LSR_TSE) == 0);
    write_8_bits(UART_DAT, chr);
}

void uart_puts(const char* str){
    for (int i = 0; str[i] != '\0'; i++)
        uart_put((char) str[i]);
}

void uart_get(void){
    uart_puts("ERROR: Not Implemented Yet!\n");
}
