# ----------------------------------------------------------
# 命令行参数
# ----------------------------------------------------------

# arm-gcc 交叉编译器参数
#		1. 本地系统相关
#			-notstdlib: 链接所有可重定位文件时不链接 LD_LIBRARY_PATH 包含的库, 只链接用户指定的库, 这里是链接-static-libgcc和-shared-libgcc参数指定
#					    使用这个选项的原因是GCC编译得到的文件可能会调用memcpy, memset等函数调用, 这里是不使用系统自带的这些函数的实现, 而是使用X2W-OS的实现
#			-notstdinc: 预处理时候搜索不在系统默认的头文件搜索路径中搜索头文件, 只搜索用户指定的库, 这里是搜索-I参数指定的文件夹
#			-fno-builtin: 不将与库函数同名的函数视为库函数, 即使用自己编写的库函数
#		2. 生成指令相关
#			-march: 设置生成(指令所构成的)二进制文件所使用的指令集(指令所属于的指令集), 这里是包含IMAFD模块在内的64位指令
#			-mabi: 设置数据模型. int/long/pointer等数据类型在32/64位系统上的长度是不一样的.
#				   LP64是指: char是8bit, short是16bit, int是32bit, long是64bit, long long是64bit, pointer是64bit
#				   参考: https://www.cnblogs.com/lsgxeva/p/7614856.html
#			-fno-pie: 不生成位置无关(Position-Independent-Code)的可执行代码. 因为生成的是内核代码, 因此要给出绝对地址, 不能是可重定位的地址
#					  -fPIC与-fpic都是在编译时加入的选项, 用于生成位置无关的代码. 这两个选项都是可以使代码在加载到内存时使用相对地址, 所有对固定地址的访问都通过全局偏移表(GOT)来实现. -fPIC和-fpic最大的区别在于是否对GOT的大小有限制. -fPIC对GOT表大小无限制, 所以如果在不确定的情况下，使用-fPIC是更好的选择
#				      -fPIE与-fpie是等价的. 这个选项与-fPIC/-fpic大致相同, 不同点在于: -fPIC用于生成动态库，-fPIE用与生成可执行文件.
#				  	  参考: https://www.cnblogs.com/20170722-kong/articles/12291904.html 
#			-mcmodel=medany: 设置相对寻址范围. medany模式可以访问当前PC的后2GiB(PC ~ PC + 2GiB)的地址空间
#					  编译的过程中, 编译器是不知道要操作的数据在哪里的, 计算数据的地址的工作是在链接阶段实现的. 
#					  也就是说，编译器需要先把拿取数据的汇编指令定下来, 在编译结束之后, 链接器进行重定位计算时再填上指令的操作数是多少. 那么就有一个问题, 编译器如何选择一个合适的指令拿取数据?
#					  mcmodel选项就是做这个事情的, 这个选项的本意是告诉编译器, 编译时候可以假定可以假设代码里面所有的符号的位置都在某个位宽(32bit)的范围之内, 而后生成对应的计算地址的指令.
#					  例如-mcmodel=small, 就是假设所有符号都在4GB范围内, 32个bit的位宽就可以寻到符号的位置, 那我们就用AUIPC指令就可以了
#					  参考1: https://bbs.huaweicloud.com/blogs/272527
#					  参考2: https://blog.csdn.net/zoomdy/article/details/100699108 
#					  参考3: https://www.francisz.cn/2020/04/14/riscv-code-models/ 
#		3. 编译相关
#			-I: 预处理时候寻找头文件的路径
#			-save-temps -dumpdir xxx/: 保存编译过程中的中间文件到xxx目录下, 这里是保存到build/temps/目录下. 中间文件包括预处理之后的源码, 编译之后的汇编代码等等, 主要是为了展开宏方便debug
#							 参考: https://blog.csdn.net/weixin_34384915/article/details/94730345
#			-O0: 设置gcc编译时的优化等级, 0表示禁止优化
#			-fomit-frame-pointer: 在不需要的时候忽略掉帧指针. 主要目的是在有些时候为函数提供一个额外的fp(frame pointer)寄存器作为通用寄存器用, 以实现一个微小的性能提升. 优化等级为O1, O2, O3的时候会自动打开
#			-g: 编译时向生成的二进制文件中写入debug信息, 同时禁止gcc在编译时为了加速对一些诸如abs，strncpy等进行重定义的行为
# 		4. 编译警告和错误相关
#			-Wall: 编译的时候显示所有的警告, 包括一般的警告和编译器认为会出现错误的警告
#			-Wmissing-prototypes: 如果没有预先声明函数原型就定义了全局函数, 编译器就发出警告. 这个选项的目的是强制所有函数在头文件中提供函数原型, 方便VSCode的intellsense分析, 补全
#			-Werror=strict-prototypes: 将调用函数时候传入的参数类型和函数原型中的类型不匹配的警告视作为错误, 主要是为了规范代码习惯
#			-Werror=incompatible-pointer-types: 同上, 将指针类型不兼容警告视为错误, 即禁止默认的指针类型转换, 必须显示进行类型转换, 也是为了规范代码习惯
CFLAGS = \
	-nostdlib \
	-nostdinc \
	-fno-builtin \
	-fno-pie \
	-march=armv9-a \
	-g \
	-O0 \
	-I include/ \
	-fomit-frame-pointer \
	-Wall \
	-Wmissing-prototypes \
	-Werror=strict-prototypes \
	-Werror=incompatible-pointer-types \

#	-save-temps -dumpdir=${BDIR}/temps/ \

# QEMU 参数
#		1. -nographic: 不显示图形界面
#		2. -smp: 设置 CPU 数
#		3. -machine: 设置模拟的系统类型. QEMU 有 User 和 System 两种模拟方式.
#					 User 模拟模式会模拟对应的CPU(例如 qemu-riscv64 会模拟64位的 RISC-V CPU), 而后将会使用Linux进程来运行交叉编译的程序, 并且会在运行时对系统调用进行翻译
#				     Full System 模拟模式将会模拟一个完整的系统, 即虚拟机. 模拟的完整系统中包括: CPU 和其他外围设备(硬盘, 网卡)
#					 在运行 Full System 模拟的时候, 你可以使用预设的一些系统, 这些系统中已经包含了指定的设备.
#					 例如当你运行 qemu-system-aarch64 的时候, 你可以指定 -machine 参数为 raspi3b 来运行一个具有树莓派3B所有设备的虚拟机, 即模拟一个树莓派3B
#					 这里指定 -machine 参数为 virt 即模拟一个具有常用设备的 RISC-V 内核的CPU
#		4. -bios: set your bios program. None means using QEMU bios.
# qemu-system-arm -machine vexpress-a9 -kernel kernel-qemu -m 128M -nographic -smp 2 -bios sbi-qemu -drive file=sdcard.img,if=none,format=raw,id=x0  -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 -initrd initrd.img
Q_FLAG = -nographic \
	-smp 1 \
	-machine vexpress-a9 \
	-m 64M 

Q_BIOS = -bios none -device loader,file=${BDIR}/os.bin,addr=0x80200000



# ----------------------------------------------------------
# 工具配置
# ----------------------------------------------------------

# QEMU
QEMU := qemu-system-arm

# cross-compiler prefix
CROSS_COMPILE := arm-none-eabi-

# GDB
GDB := $(shell \
	if gdb-multiarch -v 2>&1 | grep 'GNU' >/dev/null 2>&1; then\
		echo 'gdb-multiarch'; \
	elif ${CROSS_COMPILE}gdb -v 2>&1 | grep 'GNU' >/dev/null 2>&1; then \
		echo 'riscv64-unknown-elf-gdb'; \
	else \
		echo "Error: Cannot find gdb-multiarch or riscv64-unknown-elf-gdb!" 1>&2; \
		exit 1; \
	fi \
)

# GCC
CC := $(shell \
	if ${CROSS_COMPILE}gcc --version 2>&1 | grep 'Free' >/dev/null; then\
		echo '${CROSS_COMPILE}gcc'; \
	else \
		echo "Error: Cannot find ${CROSS_COMPILE}gcc!" 1>&2; \
		exit 1; \
	fi \
)

# LD
LD := $(shell \
	if ${CROSS_COMPILE}ld --version 2>&1 | grep 'GNU' >/dev/null; then\
		echo '${CROSS_COMPILE}ld'; \
	else \
		echo "Error: Cannot find ${CROSS_COMPILE}ld!" 1>&2; \
		exit 1; \
	fi \
)

# NM
NM := $(shell \
	if ${CROSS_COMPILE}nm --version 2>&1 | grep 'GNU' >/dev/null; then\
		echo '${CROSS_COMPILE}nm'; \
	else \
		echo "Error: Cannot find ${CROSS_COMPILE}nm!" 1>&2; \
		exit 1; \
	fi \
)

# OBJCOPY
OBJCOPY := $(shell \
	if ${CROSS_COMPILE}objcopy --version 2>&1 | grep 'GNU' >/dev/null; then\
		echo '${CROSS_COMPILE}objcopy'; \
	else \
		echo "Error: Cannot find ${CROSS_COMPILE}objcopy!" 1>&2; \
		exit 1; \
	fi \
)

# OBJDUMP
OBJDUMP := $(shell \
	if ${CROSS_COMPILE}objdump --version 2>&1 | grep 'GNU' >/dev/null; then\
		echo '${CROSS_COMPILE}objdump'; \
	else \
		echo "Error: Cannot find ${CROSS_COMPILE}objdump!" 1>&2; \
		exit 1; \
	fi \
)

# STRIP
STRIP := $(shell \
	if ${CROSS_COMPILE}strip --version 2>&1 | grep 'GNU' >/dev/null; then\
		echo '${CROSS_COMPILE}strip'; \
	else \
		echo "Error: Cannot find ${CROSS_COMPILE}strip!" 1>&2; \
		exit 1; \
	fi \
)

# REALPATH
REALPATH := $(shell \
	if uname -a | grep 'Darwin' >/dev/null 2>&1; then\
		echo 'grealpath'; \
	else \
		echo 'realpath'; \
	fi \
)


# ----------------------------------------------------------
# 源文件设置
# ----------------------------------------------------------

# kernel source dirs
K_SRCS_DIR := fs main devices
# kernel assembly source files
K_SRCS_ASM := $(foreach dir, $(K_SRCS_DIR), $(wildcard $(dir)/*.S))
# kernel c source files
K_SRCS_C := $(foreach dir, $(K_SRCS_DIR), $(wildcard $(dir)/*.c))


# ----------------------------------------------------------
# 宏设置
# ----------------------------------------------------------

# 编译生成的内核的名字
KNAME := main.elf

# 获取当前正在执行的makefile的绝对路径
MKP := $(abspath $(lastword $(MAKEFILE_LIST)))
# 根文件夹
RDIR := $(shell dirname ${MKP})
# 编译文件夹
BDIR := $(shell dirname ${MKP})/build

# 内核相关文件
KFILE := \
	${RDIR}/${KNAME} \
	${BDIR}/main.elf \
	${BDIR}/main.bin \
	${BDIR}/main.debug

# 内核目标文件
K_OBJS = $(K_SRCS_ASM:.S=.o)	# 将 K_SRCS_ASM 中的所有.S结尾的文件转换为.o结尾的文件, 并赋值给 K_OBJS 变量
K_OBJS += $(K_SRCS_C:.c=.o)		# 将 K_SRC_C 中的所有.c结尾的文件转换为.o结尾的文件, 并添加给 K_OBJS 变量
K_OBJS := $(addprefix ${BDIR}/, ${K_OBJS})	# 为 K_OBJS 变量中的所有值添加 BDIR 前缀


# ----------------------------------------------------------
# 隐式目标
# ----------------------------------------------------------

# compile all .c file into .o
${BDIR}/%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

# compile all .S file into .o
${BDIR}/%.o: %.S
	${CC} ${CFLAGS} -c -o $@ $<


# echo 伪目标debug用
.PHONY: echo
echo:
	@echo ""
	@echo ${GDB}
	@echo "Kernel 宏:"
	@echo ${K_SRCS_ASM}
	@echo ${K_SRCS_C}
	@echo ${K_OBJS}
	@echo "--------------------------------------------------------------------------------"

# ----------------------------------------------------------
# 编译目标
# ----------------------------------------------------------

# all 是默认目标, 将会:
#		1. 创建 build 编译文件夹
#		2. 编译得到内核
#		3. 编译得到SBI
.DEFAULT_GOAL := all
all: mkdir kernel $(KFILE)
	@echo '运行 `make info`查看内核文件'

# full 目标, 将会:
#		1. 完成 all 目标
#		3. 反汇编内核, 得到内核的汇编代码和内核的符号表
full: all disasm

# mkdir 伪目标将会:
#		1. 创建 build 编译文件夹
#		2. 创建 build/disasms 反汇编文件夹
#		3. 创建和源代码目录对应的 build/${K_SRCS_DIR} 文件夹
.PHONY: mkdir
mkdir:
	@mkdir -p ${BDIR}/disasms
	@mkdir -p ${BDIR}/temps
	@mkdir -p $(foreach dir, $(K_SRCS_DIR), ${BDIR}/$(dir))

.PHONY: info
info: kernel
	@echo "/* -------------------------- 内核文件 -------------------------- */"
	@echo "内核文件:"
	@for x in $(KFILE); do \
		printf "\t"; \
		${REALPATH} --relative-to ${RDIR} $$x; \
	done

# obj 目标将会:
#		1. 更新所有的目标文件
#		2. 输出内核所有的目标文件
#		3. 输出SBI所有的目标文件
# 需要注意的是, 如果不把 K_OBJS 显示声明为依赖, 那么 VSCode 的 makefile-tools 解析时候就会卡死
obj: mkdir ${K_OBJS} ${S_OBJS}
	@echo "/* -------------------------- 编译内核源文件 -------------------------- */"
	@echo "当前内核目标文件:"
	@for x in ${K_OBJS}; do \
		printf "\t"; \
		${REALPATH} --relative-to ${RDIR} $$x; \
	done
	@echo "-----------------------------------------------------------------------"

# kernel 目标依赖于 K_OBJ 目标, 具体来说会:
#		1. 根据 main.ld 链接脚本链接所有的目标文件以生产ELF格式内核文件
#		2. 将二进制内核文件转换为裸二进制文件 main.bin 以删除ELF文件中没有用到的段, 为后续的反汇编进行准备
# 		3. 将 build 文件下的 main.elf 文件去除符号表后输出为根目录下的 ${KNAME} 文件
#		4. 生成内核的符号文件并输出为 build/main.debug 文件, 方便 GDB debug用
kernel: mkdir ${K_OBJS}
	@${LD} ${K_OBJS} -T ${RDIR}/main.ld -o ${BDIR}/main.elf
	@${OBJCOPY} -O binary ${BDIR}/main.elf ${BDIR}/main.bin
	@${STRIP} ${BDIR}/main.elf -o ${RDIR}/${KNAME}
	@${OBJCOPY} --only-keep-debug ${BDIR}/main.elf ${BDIR}/main.debug


# disasm 目标依赖于 kernel 目标, 具体来说会:
#		1. 反汇编得到内核的汇编代码
#		2. 输出内核的二进制内容
#		3. 输出内核的符号表
#		4. 反汇编得到SBI的汇编代码
#		5. 输出SBI的二进制内容
#		6. 输出SBI的符号表
disasm: kernel
	@echo "内核的反汇编代码可以在文件" build/disasms/main.code "查看"
	@${OBJDUMP} -S ${BDIR}/main.elf > ${BDIR}/disasms/main.disasm
	@echo "内核的二进制内容可以在文件" build/disasms/main.machine "查看"
	@hexdump -C ${BDIR}/main.bin > ${BDIR}/disasms/main.machine
	@echo "内核的符号表可以在文件" build/disasms/main.symbol "查看"
	@echo '内核文件: 符号地址 (符号长度) 符号类型 符号名 符号定义处' > ${BDIR}/disasms/main.symbol
	@echo '常见符号类型 (更多符号类型请参考 man nm):' >> ${BDIR}/disasms/main.symbol
	@echo '\tA:\t\t该符号的值在今后的链接中将不再改变' >> ${BDIR}/disasms/main.symbol
	@echo '\tB:\t\t该符号位与BSS段中, 通常是未初始化的全局变量' >> ${BDIR}/disasms/main.symbol
	@echo '\tb:\t\t该符号位与BSS段中, 通常是未初始化的静态全局变量, 例如: static int test' >> ${BDIR}/disasms/main.symbol
	@echo '\tD:\t\t该符号位与普通的数据段中, 通常是已经初始化的全局变量' >> ${BDIR}/disasms/main.symbol
	@echo '\tt/T:\t该符号位与代码段中, 通常是全局非静态函数' >> ${BDIR}/disasms/main.symbol
	@echo '\tR:\t\t该符号位与只读数据区' >> ${BDIR}/disasms/main.symbol
	@echo '\tU:\t\t该符号未在当前文件中定义过, 需要自其他对象文件中链接进来' >> ${BDIR}/disasms/main.symbol
	@echo '\tW:\t\t未明确指定的弱链接符号, 若链接的其他对象文件中有它的定义就链接, 否则就用一个系统指定的默认值, 通常是动态链接库' >> ${BDIR}/disasms/main.symbol
	@${NM} -l -n -S -A --print-armap ${BDIR}/main.elf >> ${BDIR}/disasms/main.symbol



# clean 伪目标将会:
#		1. 清除 build 目录下的中间文件
#		2. 删除 Doxygen 文档
#		3. 删除 Sphinx 文档
.PHONY: clean
clean:
	rm -f ${RDIR}/main.elf
	rm -rf ${BDIR}/*



# ----------------------------------------------------------
# 命令行工具
# ----------------------------------------------------------


# kill 伪目标将会:
#		1. 终止所有QEMU进程
#		2. 终止所有Python.HttpServer进程
#		3. 终止所有的GDB进程
# BSD的xargs和Linux的xargs不一致, 所以需要使用test屏蔽
.PHONY: kill
kill:
	@echo "正在终止所有 QEMU 进程..."
	@qemu_process=`ps aux | grep -e 'qemu' | grep -v 'grep' | grep $$USER | awk '{print $$2}'`; \
		test $$qemu_process && (kill -9 $$qemu_process && echo "\t已杀死 QEMU 进程: $$qemu_process") || echo "\t未检测到遗留的 QEMU 进程"
	@echo "正在终止所有 Python.HttpServer 进程..."
	@pysv_process=`ps aux | grep -e 'http.server' -e 'SimpleHTTPServer' | grep -v 'grep' | grep $$USER | awk '{print $$2}'`; \
		test $$pysv_process && (kill -9 $$pysv_process && echo "\t已杀死 Python HttpServer 进程: $$pysv_process") || echo "\t未检测到遗留的 Python HttpServer 进程"
	@echo "正在终止所有 GDB 进程..."
	@gdb_process=`ps aux | grep -e 'gdb' | grep -v 'grep' | grep $$USER | awk '{print $$2}'`; \
		test $$gdb_process && (kill -9 $$gdb_process && echo "\t已杀死 GDB 进程: $$gdb_process") || echo "\t未检测到遗留的 GDB 进程"


# run 目标依赖于 kernel sbi 目标, 将会:
#		1. 使用 QEMU 运行内核
.PHONY: run
run: kernel sbi
	@echo '运行内核: ${KNAME}, 所有输出将在下方显示'
	@echo "首先按下 Ctrl+A, 然后按下 X 键以退出 QEMU"
	@echo '你可以运行 `make debug-gdb` 以使用 GDB 调试内核'
	@echo '或者运行 `make debug-vscode` 以使用 VSCode 链接 QEMU 调试内核'
	@echo "----------------------------------------------------------------------------"
	@${QEMU} ${Q_FLAG} ${Q_BIOS} -kernel ${RDIR}/${KNAME}

# debug-gdb 目标依赖于 kernel sbi 目标, 将会使用 gdb 调试内核:
#		1. qemu -kernel: 指定要调试的ELF格式二进制内核文件
#		2. qemu -s: 使用 QEMU 的 GDB Server 调试内核, 默认端口是 1234
#		3. qemu -S: 启动 QEMU 后停止 CPU 运行, 直到 GDB 客户端连接到 QEMU GDB Server
#		4. qemu &: 在后台运行 QEMU, 并在前台运行 GDB
#		5. GDB -q: 取消 GDB 链接时的一些输出信息
#		6. GDB -x: 设置 GDB 启动后运行的命令, 这里包含: 链接到 GDB Server, 在 _start 处设置断点
.PHONY : debug-gdb
debug-gdb: kernel sbi ${BDIR}/os.debug ${BDIR}/sbi.debug
	@echo "使用 GDB 调试内核, 所有输出将在下方显示"
	@echo "按下 Ctrl+C 以终止QEMU, 然后输入 quit 退出 GDB"
	@echo '你可以运行 `make run` 以使用 QEMU 直接运行内核'
	@echo '或者运行 `make debug-vscode` 以使用 VSCode 链接 QEMU 调试内核'
	@echo "------------------------------------------------------------------"
	@${QEMU} ${Q_FLAG} ${Q_BIOS} -kernel ${RDIR}/${KNAME} -gdb tcp::1234 -S &
	@cd ${RDIR} && ${GDB} ${RDIR}/${KNAME} -q -x ${RDIR}/gdbinit

# debug-server 目标依赖于 kernel sbi 目标, 将会使用 vs-code 调试内核:
.PHONY : debug-vscode
debug-vscode: kernel sbi
	@echo "使用 VSCode 调试内核, 正在等待 VSCode 链接..."
	@echo "VSCode 终止调试后 QEMU 将自动停止运行"
	@echo "如果你想直接停止运行, 则首先按下 Ctrl+A, 然后按下 X 键以退出 QEMU"
	@echo '你可以运行 `make run` 以使用 QEMU 直接运行内核'
	@echo '你可以运行 `make debug-gdb` 以使用 GDB 调试内核'
	@echo "------------------------------------------------------------------"
	@${QEMU} ${Q_FLAG} ${Q_BIOS} -kernel ${RDIR}/${KNAME} -gdb tcp::1234 -S

