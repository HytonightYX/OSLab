//
// Created by 胡思源 on 2019-04-21.
//
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SHM_SIZE 256

int main(int argc, const char* argv[]) {
    int len  = 0;

    // input array len from command
    if (argc > 1) {
        sscanf(argv[1], "%d", &len);
    }

    int segment_id = shmget(IPC_PRIVATE, SHM_SIZE * sizeof(int), S_IRUSR | S_IWUSR);
    int * fib;
    fib = (int*) shmat(segment_id, NULL, 0);
    memset(fib, 0, sizeof(int *));

    // fork a child
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed!\n");
    } else if (pid == 0) {
        // in child, produce fib arrays, stored in shared memory
        fib[0] = 1;
        fib[1] = 1;
        for (int i = 2; i <= len; ++i) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }
    } else if (pid > 0) {
        // whenever a element is calculated by child process, print the element
        int i = 0;
        while (i <= len) {
            while (fib[i] && i <=len) {
                printf("fib[%d] = %d\n", i, fib[i]);
                i++;
            }
        }
    }
}