#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(2, "usage: sleep <ticks>\n");
        exit(1);
    }

    int tm = atoi(argv[1]);
    if (tm < 0){
        fprintf(2,"sleep: ticks must be non-negative\n");
        exit(1);
    }
    sleep(tm);
    exit(0);

}