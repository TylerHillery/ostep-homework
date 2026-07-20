/*
 * Write a program that opens a file (with the open() system call)
 * and then calls fork() to create a new process. Can both the child
 * and parent access the file descriptor returned by open()?
 * What happens when they are writing to the file concurrently, i.e., at the
 * same time?
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

  FILE *r_fp = fopen("read.txt", "w+");
  FILE *w_fp = fopen("write.txt", "w+");

  if (r_fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  if (w_fp == NULL) {
    fclose(r_fp);
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  pid_t pid;

  fputs("Hello, World!", r_fp);
  rewind(r_fp);

  pid = fork();

  switch (pid) {
  case -1: {
    perror("fork");
    fclose(r_fp);
    fclose(w_fp);
    exit(EXIT_FAILURE);
  }
  case 0: {
    // child
    char buf[BUFSIZ];
    printf("r_fp %p\n", r_fp);
    printf("w_fp %p\n", w_fp);
    while (fgets(buf, sizeof(buf), r_fp) != NULL) {
      fprintf(w_fp, "CHILD: %s", buf);
    }
    printf("CHILD: %s\n", buf);
    break;
  }
  default: {
    // parent
    char buf[BUFSIZ];
    printf("r_fp %p\n", r_fp);
    printf("w_fp %p\n", w_fp);
    while (fgets(buf, sizeof(buf), r_fp) != NULL) {
      fprintf(w_fp, "PARENT: %s", buf);
    }
    printf("PARENT: %s\n", buf);
    break;
  }
  }
  fclose(r_fp);
  fclose(w_fp);
  return EXIT_SUCCESS;
}