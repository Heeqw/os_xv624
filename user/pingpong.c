#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/*
    int pipe(int*);  
    int read(int, void*, int);  
    int fork(void);  
    int getpid(void);  

    p[0] —— 管道的读取端
    p[1] —— 管道的写入端
*/
int main(int argc, char *argv[]){
    int ptoc_fd[2];  // 父进程到子进程的管道
    int ctop_fd[2];  // 子进程到父进程的管道
    int pid;
    char buf[10];

    // 检查命令行参数
    if (argc > 1){
        fprintf(2, "Usage: pingpong");
        exit(1);
    }

    pipe(ptoc_fd);  // 创建父到子的管道
    pipe(ctop_fd);  // 创建子到父的管道
    pid = fork();  // 创建子进程

    if (pid < 0){
        exit(1);  // fork 失败
    }
    // 子进程
    if (pid == 0){
        int parent_pid;
        read(ptoc_fd[0], &parent_pid, sizeof(parent_pid));  // 读取父进程 PID
        read(ptoc_fd[0], buf, 4);  // 读取 "ping"
        printf("%d: received ping from pid %d\n", getpid(), parent_pid);  // 子进程输出
        write(ctop_fd[1], "pong", strlen("pong"));  // 发送 "pong" 给父进程
    }
    // 父进程
    else{
        int parent_pid = getpid();
        write(ptoc_fd[1], &parent_pid, sizeof(parent_pid));  // 发送父进程 PID
        write(ptoc_fd[1], "ping", strlen("ping"));  // 发送 "ping" 给子进程
        wait(0);  // 等待子进程结束
        read(ctop_fd[0], buf, 4);  // 读取 "pong"
        printf("%d: received pong from pid %d\n", getpid(), pid);  // 父进程输出
    }
    exit(0);
}