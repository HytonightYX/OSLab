//
// Created by 胡思源 on 2019-05-21.
// 读者-写者问题 读者优先
//
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define MAXN 100

int writerCount = 0;
int readerCount = 0;

pthread_t writer_id[MAXN];
pthread_t reader_id[MAXN];

// 互斥锁
pthread_mutex_t mutex_read;
pthread_mutex_t mutex_write;

// 信号量
sem_t sem_read;
sem_t sem_write;

struct arg_type
{
    int rw_id;
    int arrive_time;
    int exec_time;
};

void *Reader(void *arg)
{
    struct arg_type *para = (struct arg_type *) arg;
    int arrive_time = para->arrive_time;
    int id = para->rw_id;
    int exec_time = para->exec_time;

    sleep(arrive_time);
    printf("    读者 %d 到达,申请读数据\n", id);

    pthread_mutex_lock(&mutex_read);
    // 临界区
    sem_wait(&sem_read);

    readerCount++;
    if (readerCount == 1) {
        pthread_mutex_lock(&mutex_write);
    }
    sem_post(&sem_read);

    pthread_mutex_unlock(&mutex_read);

    printf("    读者 %d 开始读数据\n", id);
    sleep(exec_time);
    printf("    读者 %d 读完数据退出\n", id);


    sem_wait(&sem_read);
    // 临界区 修改readerCount
    readerCount--;
    if (readerCount == 0) {
        pthread_mutex_unlock(&mutex_write);
    }
    sem_post(&sem_read);

    pthread_exit(0);
}

void *Writer(void *arg)
{
    struct arg_type *para = (struct arg_type *) arg;
    int arrive_time = para->arrive_time;
    int id = para->rw_id;
    int exec_time = para->exec_time;

    sleep(arrive_time);
    printf("    写者 %d 到达,申请写数据\n", id);

    sem_wait(&sem_write);
    // 临界区
    writerCount++;
    if (writerCount == 1) {
        // 阻塞后来的读者
        pthread_mutex_lock(&mutex_read);
    }
    sem_post(&sem_write);

    pthread_mutex_lock(&mutex_write);
    // 临界区
    printf("    写者 %d 开始写数据\n", id);
    sleep(exec_time);
    printf("    写者 %d 写完数据退出\n", id);
    pthread_mutex_unlock(&mutex_write);

    sem_wait(&sem_write);
    // 临界区 独占writeCount
    writerCount--;
    if (writerCount == 0) {
        // 允许后来读者加入待读队列
        pthread_mutex_unlock(&mutex_read);
    }

    sem_post(&sem_write);

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    // 从一行中读入的数据
    int t_id;
    char RW_type;
    int arrive_time;
    int exec_time;


    int wid = 1;
    int rid = 1;

    // 初始化互斥量
    pthread_mutex_init(&mutex_write,NULL);
    pthread_mutex_init(&mutex_read,NULL);

    sem_init(&sem_write, 0, 1);	//初始化信号量sem_write为1
    sem_init(&sem_read, 0, 1);	//初始化信号量sem_write为1

    freopen("input.txt","r",stdin);// 按顺序读入（仅此一行）
    while(1) {
        scanf("%d", &t_id);
        // 如果遇到 -1 则退出
        if (t_id == -1) break;
        scanf(" %c%d%d", &RW_type, &arrive_time,&exec_time);
        printf("读入: %d %c 到达时间:%d 执行时间:%d\n",t_id ,RW_type, arrive_time, exec_time);

        //  这根据读入类型创建读者写者线程
        if (RW_type == 'R') {
            //创建读者线程
            struct arg_type *arg;
            arg = (struct arg_type *)malloc(sizeof (struct arg_type));
            arg->arrive_time = arrive_time;
            arg->rw_id = rid++;
            pthread_create(&reader_id[rid], NULL, Reader, arg);
        } else if (RW_type == 'W') {
            //创建写者线程
            struct arg_type *arg;
            arg = (struct arg_type *)malloc(sizeof (struct arg_type));
            arg->arrive_time = arrive_time;
            arg->rw_id = wid++;
            pthread_create(&writer_id[wid], NULL, Writer, arg);
        }
    }
    printf("\n读者有%d个 写者有%d个\n---------开始操作---------\n", rid-1, wid-1);

    for (int i = 0; i < rid - 1; i++) {
        pthread_join(reader_id[rid], NULL);
    }

    for (int i = 0; i < wid - 1; i++) {
        pthread_join(writer_id[rid], NULL);
    }
    return 0;
}
