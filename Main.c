#include "FCFS.h"
#include "SJF.h"
#include "HRRN.h"
#include "SJFplus.h"
#include "job.h"

int main() {
    JOB job[MAXJOB];
    init(job);
    readJOBdata(job);
    showJobs(job);
    sort_reachTime(job);
    FCFS(job, quantity);
    SJF(job, quantity);
    HRRN(job, quantity);
    SJFplus(job, quantity);
    return 0;
}
