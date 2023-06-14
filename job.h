#ifndef job_h
#define job_h
#include <stdio.h>
#include <stdlib.h>
#define MAXJOB 50

int quantity = 0; //作业总数


//PCB
typedef struct JOB 
{
    int id;//作业ID
    int reachTime;//到达时间
    int needTime;//作业长度，即需要运行的时间
    double RR;//响应比
    int waitTime;//等待时间
    int startTime;//开始时间
    int visit;          //作业是否被访问(完成)
    int endtime;        //作业结束时间
    int runtime;        //作业周转时间
    int remainNeedTime; //剩余作业长度
    int reached;        //是否到达
    struct JOB* next;
}JOB, *task;


//作业初始化
void init(JOB *job) {
    for (int i = 0; i < MAXJOB; i++) {
        job[i].id = -1;
        job[i].reachTime = 0;
        job[i].needTime = 0;
        job[i].RR = -1;
        job[i].waitTime = 0; 
        job[i].startTime = 0;
        job[i].visit = 0;
        job[i].endtime = 0;
        job[i].runtime = 0;
        job[i].remainNeedTime = 0;
        job[i].reached = 0;
    }
}


//按作业到达时间排序
void sort_reachTime(JOB *job) {
    for(int i = 0;i<quantity-1;i++) {
        for(int j = 0;j<quantity-i-1;j++) {
            if(job[j].reachTime>job[j+1].reachTime) {
                JOB temp = job[j];
                job[j] = job[j+1];
                job[j+1] = temp;           
            }
        }
    }
}

void sort_needTime(JOB *job) {
    int i,b=0,min,temp=0;
    job[0].endtime = job[0].reachTime + job[0].needTime;//结束时间=到达时间+服务时间
    for (i = 1; i < quantity; i++) {
            if (job[i].reachTime > job[0].endtime);  //作业到达系统时，第0个作业还在运行
            else b = b + 1;        //用b统计需等待作业0运行的作业个数
    }

    for (i = 1; i <= b - 1; i++) {
        if (job[i].needTime > job[i + 1].needTime) {
            min = job[i].reachTime;
            job[i].reachTime = job[i + 1].reachTime;
            job[i + 1].reachTime = min;

            min = job[i].needTime;
            job[i].needTime = job[i + 1].needTime;
            job[i + 1].needTime = min;

            temp = job[i].id;		//将第二个参数的值复制给第一个参数，返回第一个参数
            job[i].id = job[i + 1].id;
            job[i + 1].id = temp;
        }                 //按最短运行时间排序
    }
    for (i = 1; i < quantity; i++) {
        if (job[i].reachTime > job[i - 1].endtime) {     //第i个进程到达系统时，第i-1个进程已运行完毕
            job[i].endtime = job[i].reachTime + job[i].needTime;
            job[i].runtime = job[i].needTime;
        }
        else {
            job[i].endtime = job[i - 1].endtime + job[i].needTime;
            job[i].runtime = job[i].endtime - job[i].reachTime;
        }
    }
}


//读取作业信息并输出
void readJOBdata(JOB *job) {
    FILE* file;
    file = fopen("job.txt", "rw");
    if (file != NULL) {
    int i = 0;
        while (!feof(file)) {
            fscanf(file, "%d %d %d\n", &(job[i].id), &(job[i].reachTime), &(job[i].needTime));
            job[i].remainNeedTime = job[i].needTime;
            quantity++;
            i++;
        }
    } else {
        printf("打开文件失败");
    }
}


//展示初始作业序列
void showJobs(JOB job[]) {
    printf("-------------------------------------\n");
    printf("作业编号\t到达时间\t作业长度\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < quantity; i++) {
        printf("%4d\t%4d\t%4d\n", job[i].id, job[i].reachTime, job[i].needTime);
    }
    printf("-------------------------------------\n");
}

#endif