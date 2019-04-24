//
// Created by 胡思源 on 2019-04-24.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include<unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#define BUFFER_SIZE 256

/**
 * 实现system V共享内存通信模型：设计一个程序，父进程创建一个子进程，并且父子进程通过一块共享内存进行通信。具体地，
 * 1) 父进程向共享内存中写入信息，写完之后打印出这样功能的一句话：这个信息是由进程X写入的。其中，X是进程的ID号。
 * 2) 子进程从共享内存中读出信息
 */

int main(){
    // 创建一个新的共享内存对象
    int segment_id = shmget(IPC_PRIVATE, BUFFER_SIZE, S_IRUSR | S_IWUSR);
    char * shared_memory;
    printf("Creating shared memory...\n");
    if (segment_id < 0) {
        fprintf(stderr, "Fork Failed!");
        _exit(-1);
    } else {
        printf("Created successfully, segment_id is %d\n==================\n\n", segment_id);
    }

    // 系统在进程的虚拟地址空间中为其分配一块区域
    shared_memory = (char*)shmat(segment_id, NULL,0);

    pid_t pid;

    printf("start...\n");

    /* Fork a child process */
    pid = fork();

    if (pid < 0) {         /* Error occurred! */
        fprintf(stderr, "Fork Failed!");
        _exit(-1);
    } else if (pid == 0) { /* Child Process */
        printf("[Child] pid is %d\n  [Buffer]: ", getpid());
        printf("%s\n==================\n", shared_memory);
    } else {                /* Parent Process */
        printf("[Parent] pid is %d \n  [Writing]...\n==================\n", getpid());
        sprintf(shared_memory, "这个信息是由进程 %d 写入的\n", getpid());

        wait(NULL);
        // 卸载共享内存
        shmdt(shared_memory);
        // 删除共享内存
        shmctl(segment_id, IPC_RMID, 0);
        // 查看共享内存
//        system("ipcs -m");
    }

    return 0;
}
