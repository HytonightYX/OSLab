//
// Created by 胡思源 on 2019-04-10.
//
#include <sys/types.h>
#include <sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

/*
 * 1. 创建子进程，满足下列要求。
 *  1) 先让子进程输出当前所在位置
 *  2) 再让父进程在当前目录下新建一个名为hise的文件夹
 *  3) 输出子进程和父进程的pid号
 *  4) 最后让父进程将程序源码文件（.c）拷贝到新建的hise文件夹
 * */


int main() {
    pid_t pid;

    printf("start …\n");

    /* Fork a child process */
    pid = fork();

    if (pid < 0) {         /* Error occurred! */
        fprintf(stderr, "Fork Failed!");
        _exit(-1);
    } else if (pid == 0) { /* Child Process */
        printf("==================\nThis is child process, pid is %d\n", getpid());
        // 子进程输出当前所在位置
        execlp("/bin/pwd", "pwd", NULL);
    } else {                /* Parent Process */
        wait(NULL);
        printf("Child Complete\n==================\n");
        printf("This is parent process, pid is %d\nmkdir ./hise...\n", getpid());
//        下面这样新建文件夹会替换整个代码段，导致无法完成第四步
//        execlp("/bin/mkdir", "mkdir", "hise", NULL);
        mkdir("hise", 0777);
        // 拷贝源文件到hise
        printf("copy source file...\n");
        execlp("/bin/cp", "cp", "Process1.c", "./hise", NULL);
    }
    return 0;
}
