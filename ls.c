#define _GNU_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int PATH_MAX = 200;

void toLsString(struct stat fileStat[100], struct dirent files[100], int size);

int main(int argc, char const *argv[]) {
  char cwd[PATH_MAX];
  int size;
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    DIR *dir = opendir(cwd);

    struct dirent files[100];
    struct stat fileInfo[100];

    int i = 0;
    int numOfFiles = 0;
    while (1) {
      struct dirent *temp;
      struct stat temp2;

      if ((temp = readdir(dir)) != NULL) {
        struct dirent temp1 = *temp;
        char *str = temp1.d_name;
        if (str[0] != '.') {
          files[numOfFiles] = temp1;
          if ((lstat(temp->d_name, &temp2)) != -1) {
            fileInfo[numOfFiles] = temp2;
          }
          numOfFiles++;
        }
      } else {
        break;
      }

      i++;
    }
    toLsString(fileInfo, files, numOfFiles);

  } else {
    printf("failed\n");
  }

  return 0;
}

void toLsString(struct stat fileStat[100], struct dirent files[100], int size) {
  int i = 0;
  while (i < size) {
    printf((S_ISDIR(fileStat[i].st_mode)) ? "d" : "-");
    printf((fileStat[i].st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat[i].st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat[i].st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat[i].st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat[i].st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat[i].st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat[i].st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat[i].st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat[i].st_mode & S_IXOTH) ? "x" : "-");
    printf("  %u", fileStat[i].st_uid);
    printf("  %u", fileStat[i].st_gid);

    struct timespec time1 = fileStat[i].st_mtimespec;
    time_t sec = (time_t)time1.tv_sec;
    struct tm* date = localtime(&sec);

    printf("  %d/%d/%d  %d:%d", date->tm_mon, date->tm_mday, (date->tm_year - 100), date->tm_hour, date->tm_min);
    printf("  %lld", fileStat[i].st_size);
    printf("  \t%lld", fileStat[i].st_blocks);
    printf("  %s\n", files[i].d_name);
    i++;
  }
}
