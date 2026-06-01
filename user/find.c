#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"

// find all the files in a directory tree with a specific name.
// standing on the shoulder of the giant
// read ls.c to see how to access directory
// encapsulate the functionality
void check_and_print(char *path, char *target, char *exec_argv[]){
    char *p;
    // compare area: no matter it is file or directory
    // we treat them the same
    // print it out if the target hit
    // Find first character after last slash.
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
      ;
    p++; // point to pure file name
    
    // compare the file name with target
    if(strcmp(p, target) != 0){ // if not hit, just end the function
      return;
    }
    // this case will be the hit case
    if(exec_argv == 0){ // == 0 means hit
      printf("%s\n", path); // this is normal mode
    }
    else // -exec mode
    { /* Assume that exec_argv = {"echo", "hi"}
        and path = "./a/b/wc"
      */
      char *new_argv[MAXARG];
      int i = 0;
      // 0 is the real number, instead of string 0, which is 0x48 in ASCII code
      while(exec_argv[i] != 0){
        new_argv[i] = exec_argv[i];
        i++;
      }
      new_argv[i] = path; // path is mount at the last place
      new_argv[i + 1] = 0; // Null-terminated
      // new_argv becomes -> {"echo", "hi", "./a/b/wc", "0"}

      if(fork() == 0){ // child process
        exec(new_argv[0], new_argv);
        // if exec failed, will go here
        // child process has to exit, otherwise it will turn into a zombie process
        fprintf(2, "find: exec failed\n");
        exit(1);
      }
      else{ // parent process
        wait(0); // wait child process
      }
    }
}

void find(char *path, char *target, char *exec_argv[]){
    // reference from ls.c
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, O_RDONLY)) < 0){
        // 2: stderr
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
    return;
  }
  
  check_and_print(path, target, exec_argv); // we can encapsulate this function to this one-line

  switch(st.type){
  case T_DEVICE:
  case T_FILE:
    break;
  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      // make sure it's a valid i-node number first
      if(de.inum == 0)
        continue;
      // add the logic of:
      // if encounter '.' or '..', stop the find
      if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
      // no difference will return 0
      // cannot run into infinite cycle
        continue; // ignore this time by "continue"
    
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      find(buf, target, exec_argv);
    }
    break;
  }
  close(fd);
}

int main(int argc, char *argv[]){
    // if found file, print it out directly
    // if it is directory, do it recursively
    // note that if encountering "." or "..", stop doing find

    if(argc < 3){ // always remember to put "\n" at the end
        printf("Usage: find <path> <target> [-exec command...]\n");
        exit(1);
    }
    else if(argc == 3){ // a normal find
      find(argv[1], argv[2], 0); // add 0, a null pointer
    }
    // for the case of find -exec
    // don't forget to add == 0
    else if(argc >= 5 && strcmp(argv[3], "-exec") == 0){
      // argv will return a pointer, starts at argv[4]
      find(argv[1], argv[2], argv + 4);
    }
    else{
      fprintf(2, "Exception: invalid arguments\n");
      exit(1);
    }
    exit(0);
}
