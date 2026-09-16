/*
 * Alternative solution using pipe() instead of wait().
 *
 * The parent blocks in read() until the child writes one byte. The child prints
 * first, then writes to the pipe to let the parent continue.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int fds[2];

  if (pipe(fds) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();

  switch (pid) {
  case -1: {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  case 0: {
    close(fds[0]);
    printf("CHILD: hello\n");
    if (write(fds[1], "x", 1) != 1) {
      perror("write");
      exit(EXIT_FAILURE);
    }
    close(fds[1]);
    break;
  }
  default: {
    char byte;
    close(fds[1]);
    if (read(fds[0], &byte, 1) != 1) {
      perror("read");
      exit(EXIT_FAILURE);
    }
    printf("PARENT: goodbye\n");
    close(fds[0]);
    break;
  }
  }

  return EXIT_SUCCESS;
}
