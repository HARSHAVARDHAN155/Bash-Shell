#include "cshell.h"

void red_piping(char arr[],char *arg)
{
    int i = 0;
    char *brr[100];
    char *token;
    token = strtok(arr, "|");
    while (token != NULL)
    {
        brr[i] = token;
        // printf("%s\n", brr[i]);
        token = strtok(NULL, "|");
        i++;
    }
    brr[i] = NULL;
    int nn = i;

    int pipes[2];
    int k = 0;
    int fd = 0;
    int var;
    dup2(STDOUT_FILENO, var);
    while (brr[k] != NULL)
    {
        // printf("%s\n", brr[k]);
        int ty = type(brr[k]);

        int j = 0;
        char *crr[100];
        char *tt;
        tt = strtok(brr[k], " < >> >\n\t");
        while (tt != NULL)
        {
            crr[j] = tt;
            // printf("%s\n", crr[j]);
            tt = strtok(NULL, " < >> > \n\t");
            j++;
        }
        crr[j] = NULL;
        char file_name[100];

        if (ty == 2 || ty == 3)
        {
            strcpy(file_name, crr[j - 1]);
            crr[j - 1] = NULL;
        }
        pipe(pipes);
        pid_t pi = fork();

        if (pi < 0)
        {
            perror("Error in piping");
        }
        else if (pi == 0)
        {
            dup2(fd, 0);
            if (brr[k + 1] != NULL)
            {
                dup2(pipes[1], 1);
            }
            else
            {
                if (ty == 2)
                {
                    int fd = open(file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
                    dup2(fd, STDOUT_FILENO);
                }
                else if (ty == 3)
                {
                    int fd = open(file_name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
                    dup2(fd, STDOUT_FILENO);
                }
            }
            close(pipes[0]);
            if (strcmp("pinfo", crr[0]) == 0)
            {
                pin(crr, arg);
            }
            else
            {
                red(crr);
            }

            exit(0);
        }
        else
        {
            wait(NULL);
            dup2(var, STDOUT_FILENO);
            close(pipes[1]);
            fd = pipes[0];
        }
        k++;
    }
}