#include "init.h"
#include "main.h"

int main(void){
    init_all();
    // 挂起等待中断
    while (1);
    
    UNREACHABLE;
}