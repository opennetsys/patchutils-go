
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "myerror.h"
#include "interdiff.h"

char* combine_diff(char fp1[], char fp2[]) {
  int argc = 3;
  char *argv[] = {"--combine", fp1, fp2};
  char *ret = malloc(sizeof(char) * 50);

  int fd;
  char filepath[] = "/tmp/fileXXXXXX";
  fd = mkstemp(filepath);

  int out = open(filepath, O_RDWR|O_CREAT|O_APPEND, 0600);
  if (-1 == out) {
    char err[] = "error: error opening tmp file";
    strcpy(ret, err);
    return ret;
  }

  int save_out = dup(fileno(stdout));
  if (-1 == dup2(out, fileno(stdout))) {
    char err[] = "error: cannot redirect stdout";
    strcpy(ret, err);
    return ret;
  }

  if (execute(argc, argv) != 0) {
    char err[] = "error: combinediff error";
    strcpy(ret, err);
    return ret;
  }

  fflush(stdout);
  close(out);
  dup2(save_out, fileno(stdout));
  close(save_out);

  strcpy(ret, filepath);
  return ret;
}

/*
int main(int argc, char *argv[]) {
  printf("ok");
  return 0;
}
*/