//
// Created by 胡思源 on 2019-04-22.
// 计算累加和
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;
void *runner(void *param);

/*
 * argc是命令行总的参数个数
 * argv[]是argc个参数，其中第0个参数是程序的全名
 * 再之后的参数命令行后面跟的用户输入的参数*/
int main(int argc, char *argv[]) {
    pthread_t tid;
    pthread_attr_t attr;

    if (argc!=2) {
        printf("usage: exec <integer value>\n");
        return -1;
    }
    if (atoi(argv[1]) < 0) {
        printf("%d must be >= 0\n", atoi(argv[1]));
        return -1;
    }
    pthread_attr_init(&attr);
    // 传入函数指针和参数
    // tid（线程标识符指针）
    // attr 线程属性初始化
    // runner 线程运行函数的起始地址
    // argv 传入的参数
    pthread_create(&tid, &attr, runner, argv[1]);

    pthread_join(tid, NULL);
    printf("sum = %d\n",sum);
}

void *runner(void *param) {
    int i, upper = atoi(param);
    sum = 0;
    for(i = 1; i<= upper; i++)
        sum += i;
    pthread_exit(0);
}

