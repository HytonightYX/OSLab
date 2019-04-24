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

// POSIX共享内存通信模型——消费者
int main() {
    const int SIZE = 4096;
    // 共享内存区名字
    const char* shm_name = "POSIX_shm";

    int shm_fd;

    void* ptr;

    shm_fd = shm_open(shm_name, O_RDONLY, 0666);
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    // 读出共享内存内容
    printf("[读出内容]: %s", (char*)ptr);

    /* ！！最后删除这块共享内存 */
    shm_unlink(shm_name);
    return 0;
}