#include "job.h"
//计算响应比，并返回当前响应比最大的job
int calculateRR(JOB *job, int currentTime) {
    double maxRR = -1;//最高响应比
    int index;
    for (int i = 0; i < quantity && job[i].reachTime <= currentTime; i++) {
        if (job[i].visit != 1) {
            job[i].waitTime = currentTime - job[i].reachTime;
            job[i].RR = (double)job[i].waitTime / (double)job[i].needTime;
            if (job[i].RR > maxRR) {
                maxRR = job[i].RR;
                index = i;
            }
        }
    }

    if (maxRR == -1) {
        for (int i = 0; i < quantity; i++) {
            if (job[i].reachTime > currentTime && job[i].visit != 0) {
                job[i].RR = 0;
                maxRR = job[i].RR;
                index = i;
            }
        }
    }

    return index;
}

void HRRN(JOB job[], int quantity) {
    int currentTime = job[0].reachTime;
    int roundTime = 0;//周转时间
    int index;//当前响应比最大的job
    index = calculateRR(job, job[0].reachTime);

    
    printf("-------------------------------------\n");
    printf("作业编号   到达时间   开始时间   等待时间   周转时间\n");
    printf("-------------------------------------\n");
    //按行输出作业信息
    for (int i = 0; i < quantity; i++) {
        if (job[index].reachTime <= currentTime) {    //若当前作业已在等待
            job[index].startTime = currentTime; //记录开始时间
            job[index].waitTime = currentTime - job[index].reachTime; //等待时间为当前时间减等待时间
            job[index].runtime = job[index].waitTime + job[index].needTime;
            /*
                作业运行...
            */
            currentTime = currentTime + job[index].needTime;    //更新当前时间
        } else {                                              //当前作业不在等待队列中
            job[index].startTime = job[index].reachTime;    //到达时间即为开始时间
            job[index].waitTime = 0;
            currentTime = job[index].startTime + job[index].needTime;
            job[index].runtime = job[index].needTime;
        }

        printf("%-4d   %-4d   %-4d   %-4d   %-4d\n", job[index].id, job[index].reachTime, job[index].startTime, job[index].waitTime, job[index].runtime);
        roundTime = roundTime + job[index].waitTime+job[index].needTime; //更新总周转时间
        job[index].visit = 1;
        index = calculateRR(job, currentTime); //更新当前响应比最大的job，准备下一轮循环
    }

    printf("总周转时间:%d\n", roundTime);
    printf("平均周转时间:%lf", (double)roundTime / (double)quantity);
}
