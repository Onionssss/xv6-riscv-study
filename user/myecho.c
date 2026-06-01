#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

// K&R version's echo, pointer arithmetic
int main(int argc, char * argv[]){
    while(--argc > 0)
        printf("%s%s", *++argv, (argc > 1) ? " ": ""); // surounded with ()
    printf("\n");
    exit(0);
}