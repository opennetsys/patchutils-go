
#include <unistd.h>
#include "myerror.c"
#include "util.c"
#include "diff.c"
#include "interdiff.c"

int Combine(char fp1[], char fp2[]) {
  int argc = 3;
  char *argv[] = {"--combine", fp1, fp2};

  return execute(argc, argv);
}