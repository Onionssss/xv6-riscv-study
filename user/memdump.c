#include "kernel/types.h"
#include "user/user.h"

// to print the contents of the memory pointed to by data 
// in the format described by the fmt argument
// implement the function memdump(char *fmt, char *data)
/* Your memdump() should handle the following format characters:
i: print the next 4 bytes of the data as a 32-bit integer, in decimal.
p: print the next 8 bytes of the data as a 64-bit integer, in hex.
h: print the next 2 bytes of the data as a 16-bit integer, in decimal.
c: print the next 1 byte of the data as an 8-bit ASCII character.
s: the next 8 bytes of the data contain a 64-bit pointer to a C string; print the string.
S: the rest of the data contains the bytes of a null-terminated C string; print the string.
*/

void memdump(char *fmt, char *data){
    char *p = data;
    int i;
    for(i = 0; fmt[i] != '\0'; i++){
        switch (fmt[i])
        {
        case 'i':
        // 1. (int *)p: regard pointer as an integer pointer
        // 2. *(int *)p: dereference that integer pointer
            printf("%d\n", *(int *)p);
            p += 4; // print the next 4 bytes of the data as a 32-bit integer, in decimal.
            break;

        case 'p':
            printf("%lx\n", *(uint64 *)p); // this will print 0x value
            p += 8; // print the next 8 bytes of the data as a 64-bit integer, in hex.
            break;

        case 'h': // use short
            printf("%d\n", *(short *)p);
            p += 2; // print the next 2 bytes of the data as a 16-bit integer, in decimal.
            break;

        case 'c': // means a character
            printf("%c\n", *p);
            p += 1; // this is the spirit, we have to move one pointer when processing one byte
            break;
        
        // the next 8 bytes of the data contain a 64-bit pointer to a C string; print the string.
        case 's': // pointer of pointer // indirection
            {
                char *pp;
        // use uint64 to move 8 bytes at a time // then change the format to char *
                pp = (char *)(*(uint64 *)p);
                printf("%s\n", pp);
                p += 8;
                break;
            }
            
        case 'S': // the rest of the data contains the bytes of a null-terminated C string; print the string.
        /* use the strlen function */
            printf("%s\n", (char *)p); // all the characters and \0
            p += strlen(p) + 1;
            break;

        default:
            break;
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Example 1: test two 4-byte integers
        printf("Example 1:\n");
        int e1[] = {61810, 2025};
        memdump("ii", (char *)e1);

        // Example 2: test 's' (pointer's pointer)
        printf("Example 2:\n");
        char *e2 = "a string";
        memdump("s", (char *)&e2);

        // Example 3: test another 's'
        printf("Example 3:\n");
        char *e3 = "another";
        memdump("s", (char *)&e3);

        // Example 4: test mix type (大魔王)
        printf("Example 4:\n");
        struct {
            uint64 p;
            int i;
            short h;
            char c;
            char s[10];
        } e4 = { (uint64)&e4, 1819438967, 100, 'z', "xyzzy" };
        memdump("pihcS", (char *)&e4);

        // Example 5: test 'S' then consecutive 'c'
        printf("Example 5:\n");
        char e5[] = "hello\0world";
        memdump("Sccccc", e5);

    }
    exit(0);
}