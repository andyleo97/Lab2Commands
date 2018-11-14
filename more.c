#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "unistd.h"

void execute(char **args);

int main(int argc, char *argv[]) {
  execute(argv);
  return 0;
}

void execute(char **args){
    pid_t id;
    int stat;

    if ((id = fork()) < 0) {
          printf("%s\n", "Fork failed");;
          exit(1);
     }
     else if (id == 0) {
          if (execvp(*args, args) < 0) {
               printf("%s\n", "command not found: try again");
               exit(1);
          }
     }
     else {
          while (wait(&stat) != id)
          ;
     }
}
