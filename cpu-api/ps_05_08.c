/*
 * Write a program that creates two children, and connects the standard output
 * of one to the standard input of the other, using the  pipe() system call.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int fds[2];

  if (pipe(fds) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  char message[] = "Hello sibling";
  pid_t child1 = fork();

  switch (child1) {
  case -1: {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  case 0: {
    close(fds[0]);
    dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    printf("hello\n");
  }
  default: {
    break;
  }
  }

  pid_t child2 = fork();

  switch (child2) {
  case -1: {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  case 0: {
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
    char buf[100];
    fgets(buf, sizeof(buf), stdin);
    printf("got %s", buf);
    break;
  }
  default: {
    break;
  }
  }
}
