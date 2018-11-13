#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    DIR *dir = opendir(cwd);


    struct dirent *files[100];
    struct stat fileInfo[100];

    int i = 0;
    while (1) {
      struct dirent *temp;
      struct stat temp2;

      if ((temp = readdir(dir)) != NULL) {
        char* str = temp->d_name;
        if(str[0] != '.'){
        printf("%s\n", temp->d_name);
        files[i] = temp;
      }
      }
      else{
        break;
      }


      int statCheck = lstat(temp->d_name , &temp2);
      if((statCheck) != -1){
        fileInfo[i] = temp2;
      }

      i++;

    }
 // i = 0;
 //    while (i < 6) {
 //      printf("%s\n", files[i]->d_name);
 //      i++;
 //    }
  }
  else {
  printf("failed\n");
  }

  return 0;
}
