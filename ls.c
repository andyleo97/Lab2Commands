#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    DIR *dir = opendir(cwd);

    struct dirent *files[100];

    int i = 0;
    while (1) {
      struct dirent *temp;

      if ((temp = readdir(dir)) != NULL) {
        printf("%s\n", temp->d_name);
      }
      else{
        break;
      }
      files[i] = temp;
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
