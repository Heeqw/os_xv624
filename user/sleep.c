#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    // 检查命令行参数数量
    if (argc != 2){
        fprintf(2, "usage: sleep <ticks>\n");
        exit(1);
    }

    // 检查输入是否为有效的正整数
    int tm = 0;
    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (i == 0 && argv[1][i] == '-') {
            fprintf(2, "sleep: ticks must be non-negative\n");
            exit(1);
        }
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            fprintf(2, "sleep: invalid input\n");
            exit(1);
        }
        tm = tm * 10 + (argv[1][i] - '0');
    }

    // 调用系统的 sleep 函数
    sleep(tm);
    printf("(nothing happens for a little while)\n");
    exit(0);
}