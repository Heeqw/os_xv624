#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    // 检查命令行参数数量
    if (argc != 2){
        fprintf(2, "usage: sleep <ticks>\n");
        exit(1);
    }

    // 将输入参数转换为整数
    int tm = atoi(argv[1]);
    // 检查输入是否为非负数
    if (tm < 0){
        fprintf(2,"sleep: ticks must be non-negative\n");
        exit(1);
    }
    // 调用系统的 sleep 函数
    sleep(tm);
    exit(0);
}