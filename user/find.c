#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *target) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    // 尝试打开给定路径
    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    // 获取文件/目录的状态信息
    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type){
    case T_FILE:
    case T_DIR:
        // 检查当前文件或目录是否匹配目标名称
        p = path + strlen(path);
        while(p > path && *p != '/')
            p--;
        if(*p == '/')
            p++;
        if(strcmp(p, target) == 0) {
            printf("%s\n", path);
        }

        // 如果是目录，则继续在其中搜索
        if(st.type == T_DIR) {
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
                printf("find: path too long\n");
                break;
            }
            strcpy(buf, path);
            p = buf+strlen(buf);
            *p++ = '/';
            // 读取目录中的每个条目
            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if(de.inum == 0)
                    continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if(stat(buf, &st) < 0){
                    printf("find: cannot stat %s\n", buf);
                    continue;
                }
                // 跳过 "." 和 ".." 目录
                if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                    continue;
                find(buf, target); // 递归搜索
            }
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    // 检查命令行参数
    if(argc != 3){
        fprintf(2, "Usage: find <directory> <filename>\n");
        exit(1);
    }
    find(argv[1], argv[2]);
    exit(0);
}