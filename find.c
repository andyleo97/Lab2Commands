#define _GNU_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


char results[100][100];
int resultSize=0;

void findFile(char search[], char directory[]);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("%s\n", "You must only enter 3 arguments Try Again!");
    exit(1);
  }
  findFile(argv[1], argv[2]);

  printf("Found %d match(es)\n", resultSize);

  for(int i = 0; i < resultSize; i++){
    printf("%s\n", results[i]);
  }

  return 0;
}

void findFile(char search[], char directory[]) {
  DIR *dir = opendir(directory);
  if (dir != NULL) {
    struct dirent *temp;
    while ((temp = readdir(dir)) != NULL) {
        if (strcmp(temp->d_name, ".") == 0 || strcmp(temp->d_name, "..") == 0) {
          continue;
        }
        char newPath[strlen(directory) + strlen(temp->d_name) + 2];
        strcpy(newPath, directory);
        strcat(newPath, "/");
        strcat(newPath, temp->d_name);
        if (strcmp(temp->d_name, search) == 0) {
           strcpy(results[resultSize],newPath);
           resultSize++;
        }
        struct stat statTemp;
        lstat(newPath, &statTemp);
        if (S_ISDIR(statTemp.st_mode)) {
          findFile(search, newPath);
        }
      }
  } else {
    printf("%s\n", "The directory You entered could not be found Try Again!");
  }
  closedir(dir);
}
