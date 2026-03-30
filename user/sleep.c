#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// What does it do:
// pause for a user-specified number of ticks: this will be the input
// A tick is a notion of time defined by the xv6 kernel,
// namely the time between two interrupts from the timer chip.
int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(2, "Usage: sleep <ticks>\n");
        exit(1);
    }
    // use atoi(ASCII to integer) to convert string in argv to int
    int tick = atoi(argv[1]); 
    pause(tick); // this is the system call sleep()
    
    exit(0);
}