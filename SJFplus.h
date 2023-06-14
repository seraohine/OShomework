#include "job.h"

int getReachTask(JOB job[], int quantity, int currentTime) {
    int minReachTime = __INT_MAX__;
    int index = -1;
    for (int i = 0; i < quantity; i++) {
        if (job[i].reached != 1 && job[i].reachTime < minReachTime && job[i].reachTime >= currentTime) {
            job[i].reached = 1;          
            minReachTime = job[i].reachTime;
            index = i;
        }
    }
    return index;
}

int getNextTask(JOB job[], int quantity, int currentTime) {
    int minRemainTime = __INT_MAX__;
    int index = -1;
    for (int i = 0; i < quantity; i++) {
        if (job[i].reachTime <= currentTime && job[i].visit == 0) {
            job[i].reached = 1;
            if (job[i].remainNeedTime < minRemainTime) {
                minRemainTime = job[i].remainNeedTime;
                index = i;
            }
        }
    }
    return index;
}


void SJFplus(JOB job[], int quantity) {
    int completed = 0;
    int currentTime = job[0].reachTime;
    int runIndex = -1;
    int reachIndex = -1;
    double roundTime = 0;

    printf("-------------------------------------\n");
    printf("作业编号   到达时间   开始时间   等待时间   作业长度   周转时间\n");
    printf("-------------------------------------\n");

    runIndex = getNextTask(job, quantity, currentTime);
    while (completed != quantity) {
        job[runIndex].startTime = currentTime;
        /*
            作业运行...
        */
        job[runIndex].reached = 1;
        reachIndex = getReachTask(job, quantity, currentTime);

        // if (reachIndex != -1) {
        //     job[runIndex].remainNeedTime = job[runIndex].remainNeedTime - (job[reachIndex].reachTime - job[runIndex].startTime);
        //     currentTime += (job[reachIndex].reachTime - job[runIndex].startTime);
        // }

        for (int i = 0; i < quantity; i++) {
            if (reachIndex != -1) {
                job[runIndex].remainNeedTime = job[runIndex].remainNeedTime - (job[reachIndex].reachTime - job[runIndex].startTime);
                currentTime += (job[reachIndex].reachTime - job[runIndex].startTime);
            }
            if (job[runIndex].remainNeedTime > job[reachIndex].needTime && reachIndex != -1) {
                printf("%-4d   %-4d   %-4d\n", job[runIndex].id, job[runIndex].reachTime, currentTime-job[runIndex].startTime);
                runIndex = reachIndex;
            } else {
                reachIndex = getReachTask(job, quantity, currentTime);
                if (reachIndex != -1) {
                    continue;
                }
                currentTime += job[runIndex].remainNeedTime;
                job[runIndex].visit = 1;
                completed++;
                job[runIndex].runtime = currentTime - job[runIndex].reachTime;
                roundTime += job[runIndex].runtime;
                printf("%-4d   %-4d   %-4d   %-4d   %-4d   %-4d\n", job[runIndex].id, job[runIndex].reachTime, job[runIndex].startTime, job[runIndex].waitTime, job[runIndex].needTime, job[runIndex].runtime);
                runIndex = getNextTask(job, quantity, currentTime);
                break;
            }
            break;
        }

        // job[runIndex].remainNeedTime = job[runIndex].remainNeedTime - (job[reachIndex].reachTime - job[runIndex].startTime);
        // currentTime += (job[reachIndex].reachTime - job[runIndex].startTime);
        // if (job[runIndex].remainNeedTime > job[reachIndex].needTime && reachIndex != -1) {
        //     printf("%-4d   %-4d   %-4d\n", job[runIndex].id, job[runIndex].reachTime, currentTime-job[runIndex].startTime);
        //     runIndex = getNextTask(job, quantity, currentTime);
        // } else {
        //     currentTime += job[runIndex].remainNeedTime;
        //     job[runIndex].visit = 1;
        //     completed++;
        //     job[runIndex].runtime = currentTime - job[runIndex].reachTime;
        //     roundTime += job[runIndex].runtime;
        //     printf("%-4d   %-4d   %-4d   %-4d   %-4d   %-4d\n", job[runIndex].id, job[runIndex].reachTime, job[runIndex].startTime, job[runIndex].waitTime, job[runIndex].needTime, job[runIndex].runtime);
        //     runIndex = getNextTask(job, quantity, currentTime);
        // }
    }
    printf("平均周转时间:%lf\n", roundTime/(double)quantity);
}