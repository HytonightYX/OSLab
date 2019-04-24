//
// Created by 胡思源 on 2019-04-25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define BUFFER_SIZE 256

// POSIX共享内存通信模型——生产者
int main() {
    const int SIZE = 4096;
    // 共享内存区名字
    const char* shm_name = "POSIX_shm";
    const char* message_0 = "Hello,";
    const char* message_1 = "James Hu!";

    int shm_fd;
    void* ptr;

    // 映射文件描述符fd指定文件的 [off,off + len]区域至调用进程的[addr, addr + len]的内存区域
    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    /* 规定共享内存大小 */
    ftruncate(shm_fd, SIZE);
    /* 根据fd指针映射到共享内存上 */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    // 将字符写入到共享内存上
    sprintf(ptr, "%s", message_0);
    // 写完之后更新文件指针
    ptr += strlen(message_0);
    sprintf(ptr, "%s", message_1);
    ptr += strlen(message_1);

    printf("[写入内容完成]");
    return 0;
}
