/*
 * Write another program using fork(). The child process should print "hello";
 * the parent process should print "goodbye". You should try to ensure that the
 * child process always prints first; can you do this without calling wait() in
 * the parent?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

  pid_t pid;

  pid = fork();

  switch (pid) {
  case -1: {
    // error
    perror("fork");
    exit(EXIT_FAILURE);
  }
  case 0: {
    // child
    printf("CHILD: hello\n");
    break;
  }
  default: {
    for (int i = 0; i < 1000000; i++)
      ;
    printf("PARENT: goodbye\n");
    break;
  }
  }
}
