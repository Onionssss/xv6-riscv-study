#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    // xv6's printf is defined in user/user.h
    printf("Hello xv6! Welcome to Doom's first user program!\n");
    // in xv6, we can only end our program by calling exit, we cannot write return 0
    exit(0);
}