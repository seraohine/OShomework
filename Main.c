#include "FCFS.h"
#include "SJF.h"
#include "HRRN.h"
#include "SJFplus.h"
#include "job.h"
// #include "SJF4.h"
// #include "SJF3.h"

int main() {
    JOB job[MAXJOB];
    init(job);
    readJOBdata(job);
    showJobs(job);
    sort_reachTime(job);
     //FCFS(job, quantity);
     //SJF(job, quantity);
     //HRRN(job, quantity);
    SJFplus(job, quantity);
    // SJF3(job, quantity);
    return 0;
}