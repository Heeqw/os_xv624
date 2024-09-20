#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/*
    int pipe(int*);
    int read(int, void*, int);
    int fork(void);
    int getpid(void);

    p[0]—— fd pipe read from
    p[1]—— fd pipe write to
*/
int main(int argc, char *argv[]){
    int ptoc_fd[2];
    int ctop_fd[2];
    int pid;
    char buf[10];

    if (argc > 1){
        fprintf(2, "Usage: pingpong");
        exit(1);
    }

    pipe(ptoc_fd);
    pipe(ctop_fd);
    pid = fork();

    if (pid < 0){
        exit(1);
    }
    // child process
    if (pid == 0){
        int parent_pid;
        read(ptoc_fd[0], &parent_pid, sizeof(parent_pid)); // 读取父进程 PID
        read(ptoc_fd[0], buf, 4);
        printf("%d: received ping from pid %d\n", getpid(), parent_pid); // 子进程输出格式
        write(ctop_fd[1], "pong", strlen("pong"));
    }
    else{
        int parent_pid = getpid();
        write(ptoc_fd[1], &parent_pid, sizeof(parent_pid)); // 发送父进程 PID
        write(ptoc_fd[1], "ping", strlen("ping"));
        wait(0);
        read(ctop_fd[0], buf, 4);
        printf("%d: received pong from pid %d\n", getpid(), pid); // 父进程输出格式
    }
    exit(0);
}
