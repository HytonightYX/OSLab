//
// Created by 胡思源 on 2019-04-22.
// 龟兔赛跑 thread 练习

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
float rabbit_dist;
float tortoise_dist;
void *runner_rabbit(void *param);
void *runner_tortoise(void *param);

int main(int argc, char *argv[])
{
    pthread_t tid_rabbit;
    pthread_t tid_tortoise;
    pthread_attr_t attr;

    // 初始化attr！！！
    pthread_attr_init(&attr);

    if (argc!=2) {
        printf("usage: exec <integer value>\n");
        return -1;
    }
    if (atoi(argv[1]) < 0) {
        printf("%d must be >= 0\n", atoi(argv[1]));
    }

    /*
     补充代码：创建2个线程分别对应于兔子和乌龟，乌龟和兔子每小时跑的距离都是随机生成数，
     通过传入的参数设定它们一共要跑的时间（几个小时）。最后通过比较乌龟和兔子在这段时间（几个小时）所
     跑的总距离来判断龟兔赛跑的冠军。
    */
    // 兔子跑
    pthread_create(&tid_rabbit, &attr, runner_rabbit,argv[1]);
    pthread_join(tid_rabbit, NULL);
    // 输出兔子跑的总距离
    printf("rabbit's distance = %f\n\n",rabbit_dist);

    // 乌龟跑
    pthread_create(&tid_tortoise, &attr, runner_tortoise, argv[1]);
    pthread_join(tid_tortoise, NULL);
    // 输出兔子跑的总距离
    printf("tortoise's distance = %f\n\n",tortoise_dist);

    printf("[winner]: %s !", tortoise_dist > rabbit_dist ? "tortoise" : "rabbit");

    return 0;
}


void *runner_rabbit(void *param) {
    int i = 0;
    int tot_time = atoi(param);
    rabbit_dist = 0;
    int speed;
    // 提供随机化种子
    srand((unsigned)time(0) + 1);

    printf("[rabbit]\n");
    while (i < tot_time) {
        // 速度（每小时跑的距离）
        speed = (rand() % 9)+ 1;
        printf("%d hour: %d\n",i + 1, speed);
        rabbit_dist += speed;
        i++;
    }
    pthread_exit(0);
}

void *runner_tortoise(void *param) {
    int i = 0;
    int tot_time = atoi(param);
    tortoise_dist = 0;
    int speed;
    // 提供随机化种子
    srand((unsigned)time(0) + 2);

    printf("[tortoise]\n");
    while (i < tot_time) {
        // 速度（每小时跑的距离）
        speed = (rand() % 9)+ 1;
        printf("%d hour: %d\n",i + 1, speed);
        tortoise_dist += speed;
        i++;
    }
    pthread_exit(0);
}