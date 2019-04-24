//
// Created by 胡思源 on 2019-04-10.
//

#include <sys/wait.h>
#include<stdio.h>
#include<unistd.h>

int main() {
    pid_t son;

    son = fork();

    if (son == -1) /* report */
    else if (son == 0) execlp("/bin/cat", "cat", "wctrial.txt", NULL);
    else wait(NULL);

    son = fork();

    if (son == -1)
        fprintf(stdrr, "hello world!\n");
    else if (son == 0)
        execlp("/bin/mkdir", "mkdir", "mydirectory", NULL);
    else
        wait(NULL);

    return 0;
}