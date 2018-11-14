#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[]) {
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(argv[2], "r");
  if (fp == NULL){
      exit(EXIT_FAILURE);
  }
  int size = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
      if (strstr(line , argv[1] )!= NULL)
      {
         printf("%d %s\n\n", lineNum, line);
      }
      lineNum++;
  }


  fclose(fp);
  if (line)
      free(line);
  return 0;
}
