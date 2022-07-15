#include "cshell.h"

int pin(char **token, char *arg)
{
    pid_t pid;
    char path[1000];
    if (token[1] == NULL)
    {
        pid = getpid();
        strcpy(path, arg);
        path[0] = '~';
    }
    else
    {
        char buff_path[1000];
        char buff2[1000];
        long long pp = atoi(token[1]);
        // printf("%lld",pp);
        pid = (pid_t)pp;
        // printf("%d",pid);
        struct stat mystat;
        sprintf(buff_path, "/proc/%d/exe", pid);
        if (stat(buff_path, &mystat) == -1 && errno == ENOENT)
        {
            printf("Error: Cannot find process \n");
            return 0;
        }
        else
        {
            readlink(buff_path, buff2, sizeof(buff2));
            strcpy(path, buff2);
        }
    }
    char file_path[1000];
    int count = 0;
    char proc_status;
    char line[300];
    sprintf(file_path, "/proc/%d/status", pid);
    FILE *ss = fopen(file_path, "r");
    while (fgets(line, sizeof(line), ss) != NULL)
    {
        if (count == 2)
        {
            proc_status = line[7];
        }
        count++;
    }
    fclose(ss);
    char memory[1000];
    sprintf(memory, "/proc/%d/statm", pid);
    FILE *st = fopen(memory, "r");
    char mm[1000];
    printf("pid-- %d\n", pid);
    printf("Process Status-- %c\n", proc_status);
    fgets(mm, sizeof(mm), st);

    char *ll;
    ll = strtok(mm, " \t");
    printf("memory-- %s\n", ll);
    fclose(st);
    printf("Executable path-- %s\n", path);
}