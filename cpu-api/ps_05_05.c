/*
 * Now write a program that uses wait() to wait for the child process  to finish
 * in the parent. What does wait() return? What happens if  you use wait() in
 * the child?
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
    // calling wait() here I wonder if this will hang give the child has no 
    // children itself so does wait run forever then? 
    pid_t grandchild_pid = wait(NULL);
    printf("Grand child pid:%d\n", (int)grandchild_pid);
    // result: returns -1 for failure
    break;
  }
  default: {
    // parent

    // should be the same as child_pid since parent only has one child
    pid_t wpid = wait(NULL);
    printf("PARENT(%d): Hello child(pid:%d, wpid:%d)\n", (int)getpid(),
           child_pid, wpid);
    break;
  }
  }
  return EXIT_SUCCESS;
}