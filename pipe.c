#include "cshell.h"
int check_piping(char arr[])
{
    for (int i = 0; i < strlen(arr); i++)
    {
        if (arr[i] == '|')
        {
            return 1;
        }
    }
    return 0;
}

void piping(char arr[])
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
    while (brr[k] != NULL)
    {
        // printf("%s\n", brr[k]);
        int j = 0;
        char *crr[100];
        char *tt;
        tt = strtok(brr[k], " \n\t");
        while (tt != NULL)
        {
            crr[j] = tt;
            // printf("%s\n", crr[j]);
            tt = strtok(NULL, " \n\t");
            j++;
        }
        crr[j] = NULL;
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
            close(pipes[0]);
            red(crr);
            exit(0);
        }
        else
        {
            wait(NULL);
            close(pipes[1]);
            fd = pipes[0];
        }
        k++;
    }
}