//
// Created by 胡思源 on 2019-03-27.
// filetools 文件读写器

#include <stdio.h> //标准输入输出函数
#include <stdlib.h> //C、C++语言的最常用的系统函数
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX 128

int chmd() {
    int c;
    mode_t mode = S_IWUSR;
    printf("\n 0. 0700\n 1. 0400\n 2. 0200\n 3. 0100\n");
    printf("Please input your choice of change the mode of the file :");
    scanf("%d", &c);
    switch (c) {
        case 0:
            chmod("file1", S_IRWXU);
            break;
            // Mode flag: Read, write, execute by user.
            //依据上面数字的提示定义其他case中文件权限的情况。
            //补充代码：case1
        case 1:
            chmod("file1", S_IRUSR);
            break;
            //补充代码：case2
        case 2:
            chmod("file1", S_IWUSR);
            break;
            //补充代码：case3
        case 3:
            chmod("file1", S_IXUSR);
            break;
        default:
            printf("You have a wrong choice! \n");
    }
    return 0;
}

int main() {
    int fd = -1;
    int num;
    int choice;
    ssize_t ret;
    char buffer[MAX];
    struct stat st;
    char *path = "/bin/ls";
    char *argv[4] = {"ls", "-l", "file1", NULL};
    while (1) {
        printf("\n************************\n");
        printf("0. 退出\n");
        printf("1. 创建新文件\n");
        printf("2. 写文件\n");
        printf("3. 读文件\n");
        printf("4. 修改文件权限\n");
        printf("5. 查看当前文件的权限并退出\n");
        printf("*************************\n");
        printf("Please input your choice(0-6):");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                close(fd);
                exit(0);
            case 1:
                fd = open("file1", O_RDWR | O_TRUNC | O_CREAT, 0750);

//                fd=open("file1.txt",O_WRONLY | O_CREAT | O_TRUNC,0600);

                /*
                O_RDWR : file open mode: Read/Write
                O_TRUNC : file open mode: Truncate file to length 0
                O_CREAT : file open mode: Create if file does not yet exist.
                0750: file access permission bits -rwxr-x---当前用户rwx；同组用户r-x； 其他用户无权限
                */

                if (fd == -1)
                    printf("File Create Failed!\n");
                else
                    printf("fd=%d\n", fd);
                break;
            case 2:
                //补充代码：用read与write函数，从键盘里面读取信息，写到filel里面
                // read() 成功则返回读取的字节数ret，出错返回-1并设置errno，如果在调read之前已到达文件末尾，则这次read返回0，出错返回-1
                ret = read(STDIN_FILENO, buffer, MAX);

                if (ret >= 0) {
                    // 将buffer中字符写进fd中
                    write(fd, buffer, strlen(buffer));
                    // 手动将指针归位!
                    lseek(fd, -ret, SEEK_CUR);
                }
                break;
            case 3:
                //补充代码：用read与write函数，把file1文件的内容在屏幕上输出

                // 从文件指针fd中读入数据到buffer中
                ret = read(fd, buffer, MAX);

                // 将buffer中字符写到标准输出，长度为ret
                if (ret >= 0)
                    write(STDOUT_FILENO, buffer, strlen(buffer));
                break;
            case 4:
                chmd();
                printf("Change mode success!\n");
                break;
            case 5:
                execv(path, argv); //-ls -l 显示文件完整的信息，包括权限，拥有者，拥有组，文件名，大小等
                break;
            default:
                printf("You have a wrong choice!\n");
        }
    }
    return 0;
}
