#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    char cbuf[1]; // buffer for child
    char pbuf[1]; // buffer for parent
    int pparent[2]; // used for pipe
    int pchild[2];
    pipe(pparent); // parent to child
    pipe(pchild); // child to parent
    pbuf[0] = 'p';
    cbuf[0] = 'c';
 
    if(fork() == 0){ // child process
        close(pchild[0]);
        read(pparent[0], pbuf, 1);
        printf("%d: received ping\n", getpid());
        write(pchild[1], cbuf, 1);
        close(pchild[1]);
        exit(0);
    }
    else{ // pid > 0, which is parent process
        close(pparent[0]);
        write(pparent[1], pbuf, 1); // to break the deadlock, let parent write buffer first
        close(pparent[1]);
        read(pchild[0], cbuf, 1);
        printf("%d: received pong\n", getpid());
        wait(0);
        exit(0);
    }
    exit(0);
}