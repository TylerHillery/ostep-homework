/*
 * Write a program that creates a child process, and then in the child  closes
 * standard output (STDOUT FILENO). What happens if the child  calls printf() to
 * print some output after closing the descriptor?
 * 
 * Result: Nothing is printfed by the child but the parent can still print to it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(void) {

  pid_t child_pid = fork();

  switch (child_pid) {
  case -1: {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  case 0: {
    close(STDOUT_FILENO);
    errno = 0;
    printf("Lets trying printing to stdout after closing it!");
    fprintf(stderr, "errno: %d (%s)\n", errno, strerror(errno));
    break;
  }
  default: {
    waitpid(child_pid, NULL, 0);
    printf("Can't believe my child is trying to print to stdout after closing "
           "it, I'm such a terrible parent\n");
    break;
  }
  }
  return EXIT_SUCCESS;
}
