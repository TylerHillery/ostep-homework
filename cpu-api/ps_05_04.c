#define _GNU_SOURCE

/*
 * Write a program that calls fork() and then calls some form of  exec() to run
 * the program /bin/ls. See if you can try all of the  variants of exec(),
 * including (on Linux) execl(), execle(),  execlp(), execv(), execvp(), and
 * execvpe(). Why do  you think there are so many variants of the same basic
 * call?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

  pid_t cpid = fork();

  switch (cpid) {
  case -1: {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  case 0: {
    // exec
    execl("/bin/ls", "ls", "-l", NULL);

    // // execle
    // char *env[] = {"HOME=/usr/home", "LOGNAME=home", (char *)0};
    // execle("/bin/ls", "ls", "-l", (char *)0, env);

    // // execlp
    // execlp("ls", "ls", "-l", (char *)0);

    // // execv
    // char *cmd[] = {"ls", "-l", (char *)0};
    // execv("/bin/ls", cmd);

    // // execve
    // char *cmd[] = {"ls", "-l", ".", (char *)0};
    // char *env[] = {"HOME=/tmp", "LOGNAME=ostep", (char *)0};
    // execve("/bin/ls", cmd, env);

    // // execvp
    // char *cmd[] = { "ls", "-l", (char *)0};
    // execvp("ls", cmd);

    // // execvpe
    // char *cmd[] = {"ls", "-l", ".", (char *)0};
    // char *env[] = {"HOME=/tmp", "LOGNAME=ostep", (char *)0};
    // execvpe("ls", cmd, env);



    break;
  }
  default: {
    break;
  }
  }
  return EXIT_SUCCESS;
}
