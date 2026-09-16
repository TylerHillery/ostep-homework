/*
 * Alternative solution using a signal instead of wait().
 *
 * The parent pauses until it receives SIGUSR1. The child prints first, then
 * sends SIGUSR1 to its parent.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static volatile sig_atomic_t child_printed = 0;

static void handle_sigusr1(int sig) {
  (void)sig;
  child_printed = 1;
}

int main(void) {
  struct sigaction sa = {0};
  sa.sa_handler = handle_sigusr1;

  if (sigaction(SIGUSR1, &sa, NULL) == -1) {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();

  switch (pid) {
  case -1: {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  case 0: {
    printf("CHILD: hello\n");
    if (kill(getppid(), SIGUSR1) == -1) {
      perror("kill");
      exit(EXIT_FAILURE);
    }
    break;
  }
  default: {
    while (!child_printed)
      pause();
    printf("PARENT: goodbye\n");
    break;
  }
  }

  return EXIT_SUCCESS;
}
