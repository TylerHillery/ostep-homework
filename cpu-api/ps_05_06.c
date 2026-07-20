/*
 * Write a slight modification of the previous program, this time using
 * waitpid() instead of wait(). When would waitpid() be  useful?
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

  pid_t child_pid = fork();

  switch (child_pid) {
  case -1: {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  case 0: {
    // child process
    printf("CHILD(%d): Hello!\n", (int)getpid());
    break;
  }
  default: {
    // parent
    pid_t wpid = waitpid(child_pid, NULL, 0);
    printf("PARENT(%d): Hello child(pid:%d, wpid:%d)\n", (int)getpid(),
           child_pid, wpid);
    break;
  }
  }
  return EXIT_SUCCESS;
}