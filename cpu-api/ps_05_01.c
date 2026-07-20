/*
 * Write a program that calls fork(). Before calling fork(), have the  main
 * process access a variable (e.g., x) and set its value to something (e.g.,
 * 100). What value is the variable in the child process?  What happens to the
 * variable when both the child and parent change  the value of x?
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int x = 100;
  pid_t pid;
  printf("Before fork: x = %d\n", x);
  pid = fork();

  switch (pid) {
  case -1: {
    // failure
    perror("fork");
    exit(EXIT_FAILURE);
  }
  case 0: {
    // child
    printf("After fork in child: x = %d\n", x);
    x = 4;
    printf("After changing x in child: x = %d\n", x);
    break;
  }
  default: {
    // parent
    printf("After fork in parent: x = %d\n", x);
    x = 2;
    printf("After changing x in parent : x = %d\n", x);
    break;
  }
  }

  return EXIT_SUCCESS;
}
