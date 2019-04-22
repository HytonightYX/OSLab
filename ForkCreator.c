//
// Created by 胡思源 on 2019-04-10.
//
//在Linux下练习使用fork()创建进程(可参考课堂PPT)，增加全局变量，在子进程与父进程中分别对全局变量进行修改，并打印出结果。可针对下列两种情况分别设计，给出结果并分析原因。
//1) 如果父进程要等待子进程结束再进行；
//2) 如果父进程不等待子进程。


#include <sys/types.h>
#include <sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/stat.h>


int main() {
    pid_t pid;
    int a = 0;
    printf("init a = %d\n", a);

    /* Fork a child process */
    pid = fork();

    if (pid < 0) {         /* Error occurred! */

    } else if (pid == 0) { /* Child Process */
        printf("==================\nThis is child process, pid is %d\n", getpid());
        // 子进程输出当前所在位置
        execlp("/bin/pwd", "pwd", NULL);
    } else {                /* Parent Process */
        wait(NULL);
        printf("Child Complete\n==================\n");
        printf("This is parent process, pid is %d\nmkdir ./hise...\n", getpid());
        execlp("/bin/mkdir", "mkdir", "hise", NULL);
    }
}
