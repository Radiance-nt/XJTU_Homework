
PACKAGE_MANAGER=''
if apt --version | grep 'apt' >/dev/null 2>&1; then
    PACKAGE_MANAGER='apt'
elif yum --version | grep 'yum' >/dev/null 2>&1; then
    PACKAGE_MANAGER='yum'
elif brew --version | grep 'Homebrew' >/dev/null 2>&1; then
    PACKAGE_MANAGER='brew'
fi


# QEMU
if qemu-system-arm --version | grep 'QEMU' >/dev/null 2>&1; then
    echo 'qemu-system-arm found: ' && which qemu-system-arm
else
    echo 'Installing qemu-system-arm...' && ${PACKAGE_MANAGER} install qemu
fi

# Cross Compiler
if arm-none-eabi-gcc --version | grep 'Free' >/dev/null 2>&1; then
    echo 'arm-none-eabi-gcc found: ' && which arm-none-eabi-gcc
else
    if uname -a | grep 'Linux' >/dev/null 2>&1; then
        echo 'Installing arm-none-eabi-gcc...' && ${PACKAGE_MANAGER} install gcc-arm-linux-gnueabihf
    elif uname -a | grep 'Darwin' >/dev/null 2>&1; then
        echo 'Installing arm-none-eabi-gcc...' && ${PACKAGE_MANAGER} install gcc-arm-embedded
    else    
        echo 'Non-supported Platform, please download cross-compiler manually...'
    fi
fi