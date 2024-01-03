#ifndef __INCLUDE_IO_H
#define __INCLUDE_IO_H

#include "types.h"

/* ---------------------- 为VSCode提供补全 ---------------------- */

/**
 * @brief `write_8_bits`向`addr`映射的寄存器写1个字节的数据
 * 
 * @param addr 寄存器映射的地址
 * @param value 需要写入的数据, 1个字节
 */
static inline void write_8_bits(uint32_t addr, uint8_t value);

/**
 * @brief `write_16_bits`向`addr`映射的寄存器写2个字节的数据
 * 
 * @param addr 寄存器映射的地址
 * @param value 需要写入的数据, 2个字节
 */
static inline void write_16_bits(uint32_t addr, uint16_t value);

/**
 * @brief `write_32_bits`向`addr`映射的寄存器写4个字节的数据
 * 
 * @param addr 寄存器映射的地址
 * @param value 需要写入的数据, 4个字节
 */
static inline void write_32_bits(uint32_t addr, uint32_t value);

/**
 * @brief `write_64_bits`向`addr`映射的寄存器写8个字节的数据
 * 
 * @param addr 寄存器映射的地址
 * @param value 需要写入的数据, 8个字节
 */
static inline void write_64_bits(uint32_t addr, uint32_t value);


/**
 * @brief `read_8_bits`从`addr`映射的寄存器读取1个字节的数据
 * 
 * @param addr 寄存器映射的地址
 * @return uint8_t 读取的数据
 */
static inline uint8_t read_8_bits(uint32_t addr);

/**
 * @brief `read_16_bits`从`addr`映射的寄存器读取2个字节的数据
 * 
 * @param addr 寄存器映射的地址
 * @return uint16_t 读取的数据
 */
static inline uint16_t read_16_bits(uint32_t addr);


/**
 * @brief `read_32_bits`从`addr`映射的寄存器读取4个字节的数据
 * 
 * @param addr 寄存器映射的地址
 * @return uint32_t 读取的数据
 */
static inline uint32_t read_32_bits(uint32_t addr);


/* ---------------------- 实现部分 ---------------------- */

// 内联函数实现IO

/**
 * @brief `dmb`(`Define Memory Barrier`)定义了内存屏障(`Memory Barrier`)
 * @note 关于内存屏障, 参考:
 * - `GCC`优化: https://www.cnblogs.com/nufangrensheng/p/3890856.html
 * - 内存屏障原理: https://stackoverflow.com/questions/14950614/working-of-asm-volatile-memory
 */
#define dmb() __asm__ __volatile__ ("" : : : "memory")

/**
 * @brief `__iormb` 定义了读取寄存器的内存屏障
 */
#define __iormb() dmb()

/**
 * @brief `__iowmb` 定义了写入寄存器的内存屏障
 */
#define __iowmb() dmb()

/**
 * @brief `glue`用于将符号`x`, `y`, `z`拼接为符号`x_y_z`
 * 
 * @param x 第一个符号
 * @param y 第二个符号
 * @param z 第三个符号
 */
#define glue(x, y, z) x ## _ ## y ## _ ## z

/**
 * @brief `mkname`用于方便的拼接得到函数名
 * 
 * @param type 读还是写寄存器, 只能是read或write
 * @param width 读写的位数
 */
#define mkname(type, width) glue(type, width, bits)

/**
 * @brief `mkread`用于生成读不同长度寄存器的函数
 * 
 * @param width 读取的位数
 * 
 * @note 通常情况下，在内联汇编代码块的最后一条语句中将需要返回的值存储在一个特定的变量中，然后该变量将被作为代码块的返回值返回给调用者。在GCC扩展中，这个变量通常被命名为__v（两个下划线 + v），并且在代码块的最后一行写上__v;语句来表示将其作为返回值返回给调用者。
 * @note 因为地址的值(寄存器的值)可能会被设备改变, 因此必须声明是volatile, 以避免GCC进行优化 
 */
#define mkread(width) \
static inline uint##width##_t mkname(read, width)(uint32_t addr){ \
    uint##width##_t __v = *(volatile uint##width##_t*)addr; \
    __iormb(); \
    return __v; \
}

/**
 * @brief `mkwrite`用于生成写不同长度寄存器的函数
 * 
 * @param width 写入的位数
 * 
 * @note 因为地址的值(寄存器的值)可能会被设备改变, 因此必须声明是volatile, 以避免GCC进行优化 
 */
#define mkwrite(width) \
static inline void mkname(write, width)(uint32_t addr, uint##width##_t value){ \
    uint##width##_t __v = value; \
    __iowmb(); \
    *(volatile uint##width##_t*)addr = __v; \
}



mkread(8);
mkread(16);
mkread(32);

mkwrite(8);
mkwrite(16);
mkwrite(32);


#endif