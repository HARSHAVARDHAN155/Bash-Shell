#include "cshell.h"
void fg(char job_num[], int njobs)
{
    int var = atoi(job_num);
    if (strlen(job_num) < 1)
    {
        printf("please give the job number\n");
        return;
    }
    else if (var > njobs)
    {
        printf("NO job with given number exists\n");
        return;
    }
    int pid, w, s;
    pid = bg_pids[var - 1];
    bg_kills[var-1]=0;
    char job_name[100];
    strcpy(job_name, bg[var - 1]);
    kill(pid, SIGCONT);
    w = waitpid(pid, &s, WUNTRACED);
    if (WIFSTOPPED(s))
    {
        printf("%s with %d exited normally\n", job_name, pid);
    }
}

void bg_bg(char job_num[],int njobs)
{
    int var = atoi(job_num);
    if (strlen(job_num) < 1)
    {
        printf("please give the job number\n");
        return;
    }
    else if (var > njobs)
    {
        printf("NO job with given number exists\n");
        return;
    }
    int pid, w, s;
    pid = bg_pids[var - 1];
    bg_kills[var-1]=0;
    char job_name[100];
    strcpy(job_name, bg[var - 1]);
    kill(pid, SIGCONT);
}