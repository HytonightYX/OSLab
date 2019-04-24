//
// Created by 胡思源 on 2019-04-24.
//
#include <sys/types.h>
#include <sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/stat.h>

// 在Linux下练习使用fork()创建进程(可参考课堂PPT)，增加全局变量，
// 在子进程与父进程中分别对全局变量进行修改，并打印出结果。可针对下列
// 两种情况分别设计，给出结果并分析原因。

//1) 如果父进程要等待子进程结束再进行；
//2) 如果父进程不等待子进程。

// 待观察的全局变量
int g = 0;

// 父进程等待子进程
void fa_wait() {
    pid_t pid;

    printf("start …\n");

    /* Fork a child process */
    pid = fork();

    if (pid < 0) {         /* Error occurred! */
        fprintf(stderr, "Fork Failed!");
        _exit(-1);
    } else if (pid == 0) { /* Child Process */
        g += 5;
        printf("==================\nThis is child process, pid is %d\ng = %d\n", getpid(), g);
    } else {                /* Parent Process */
        // 父进程等待子进程
        wait(NULL);
        g = 10;
        printf("Child Complete\n==================\n");
        printf("This is parent process, pid is %d\ng = %d\n", getpid(), g);
    }
}

// 父进程不等待子进程
void fa_not_wait() {
    pid_t pid;

    printf("start …\n");

    /* Fork a child process */
    pid = fork();

    if (pid < 0) {         /* Error occurred! */
        fprintf(stderr, "Fork Failed!");
        _exit(-1);
    } else if (pid == 0) { /* Child Process */
        g += 5;
        printf("==================\nThis is child process, pid is %d\ng = %d\n", getpid(), g);
    } else {                /* Parent Process */
//        注释下面这句，父进程不等待子进程
//        wait(NULL);
        g = 10;
        printf("Child Complete\n==================\n");
        printf("This is parent process, pid is %d\ng = %d\n", getpid(), g);
    }
}


int main() {
    // 父进程等待子进程
    fa_wait();
    // 父进程不等待子进程
//    fa_not_wait();
    return 0;
}