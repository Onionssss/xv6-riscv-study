#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h" // for using O_RDONLY

// open and read, C strings, and processing text files
void process(int fd){
    char c; // we dig "one byte" in memory, and we call it c

    // we need a state bit to indicate if the number is valid or not
    int is_invalid = 0; // it's like dirty bit
    int has_digit = 0; // if theres was a number already
    int val = 0; // initialize number with zero
    
    // need to tell the computer what's the separator
    char *seps = " -\n\t\r,.;/"; // blank space is also a separator

    while(read(fd, &c, 1) > 0){
        // implement the state machine here
        if(c >= '0' && c <= '9'){ // to make sure c is a number between 0 and 9
            val = val * 10 + (c - '0'); // decimal operation
            has_digit = 1;
        } // test if a character matches any of the separators using strchr
        else if(strchr(seps, c)){
            // if val is a multiple of 5 or 6 and we're encountering a seperator
            if(has_digit == 1 && is_invalid == 0 && (val % 5 == 0 || val % 6 == 0)){
                printf("%d\n", val);
            } // reset the state
            val = 0;
            is_invalid = 0;
            has_digit = 0;
        }
        else{ // cannot help with this string
            is_invalid = 1;
        }
    } // implicit separator: there's no end in the last place
    if(has_digit && !is_invalid && (val % 5 == 0 || val % 6 == 0)){
        printf("%d\n", val);
    }
}

int main(int argc, char *argv[]) {
    // case 1: there's no parameter provided with sixfive
    // directly type $ sixfive
    if(argc <= 1){
        process(0);
        exit(0);
    }
    int i;
    // case 2: input given additional file
    // such as $ sixfive a.txt b.txt
    for(i = 1; i < argc; i++){
        int fd = open(argv[i], O_RDONLY);
        if(fd < 0){
            printf("sixfive: cannot open %s\n", argv[i]);
            continue;
        }
        process(fd);
        close(fd);
    }

    exit(0);
}
