#include "cshell.h"

int check_redirection(char arr[])
{
    for (int i = 0; i < strlen(arr); i++)
    {
        if (arr[i] == '<' || arr[i] == '>')
        {
            return 1;
        }
    }
    return 0;
}

int type(char arr[])
{
    int type = 0;
    for (int i = 0; i < strlen(arr); i++)
    {
        if (arr[i] == '<')
        {
            type = 1;
        }
        else if (arr[i] == '>' && arr[i + 1] == '>' && type == 1)
        {
            type = 5;
            break;
        }
        else if (arr[i] == '>' && arr[i + 1] == '>')
        {
            type = 2;
        }
        else if (arr[i] == '>' && type == 1)
        {
            type = 4;
        }
        else if (arr[i] == '>' && type != 2)
        {
            type = 3;
        }
    }
    return type;
}

void red(char *arr[])
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("error in fork");
    }
    else if (pid == 0)
    {
        if (execvp(arr[0], arr) == -1)
        {
            perror("execution failed");
        }
        exit(0);
    }
    else
    {
        wait(NULL);
    }
}

void direction(char arr[], char *arg)
{
    int typ = type(arr);
    // printf("type: %d\n", typ);
    int i = 0;
    char *brr[100];
    char *token;
    token = strtok(arr, " < >>  > \n");
    while (token != NULL)
    {
        brr[i] = token;
        token = strtok(NULL, " < >>  > \n");
        i++;
    }
    int nn = i;
    brr[i] = token;
    if (typ == 1)
    {
        red(brr);
    }
    else if (typ == 2)
    {
        char file_name[100];
        strcpy(file_name, brr[nn - 1]);
        int fd = open(file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
        int var;
        dup2(STDOUT_FILENO, var);
        dup2(fd, STDOUT_FILENO);
        brr[nn - 1] = NULL;
        if (strcmp("pinfo", brr[0]) == 0)
        {
            pin(brr, arg);
        }
        else
        {
            red(brr);
        }
        dup2(var, STDOUT_FILENO);
    }
    else if (typ == 3)
    {
        char file_name[100];
        strcpy(file_name, brr[nn - 1]);
        int fd = open(file_name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
        int var;
        dup2(STDOUT_FILENO, var);
        dup2(fd, STDOUT_FILENO);
        brr[nn - 1] = NULL;
        if (strcmp("pinfo", brr[0]) == 0)
        {
            pin(brr, arg);
        }
        else
        {
            red(brr);
        }
        dup2(var, STDOUT_FILENO);
    }
    else
    {
        if (typ == 4)
        {
            char file_name[100];
            strcpy(file_name, brr[nn - 1]);
            int fd = open(file_name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
            int var;
            dup2(STDOUT_FILENO, var);
            dup2(fd, STDOUT_FILENO);
            brr[nn - 1] = NULL;
            if (strcmp("pinfo", brr[0]) == 0)
            {
                pin(brr, arg);
            }
            else
            {
                red(brr);
            }
            dup2(var, STDOUT_FILENO);
        }
        else
        {
            char file_name[100];
            strcpy(file_name, brr[nn - 1]);
            int fd = open(file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
            int var;
            dup2(STDOUT_FILENO, var);
            dup2(fd, STDOUT_FILENO);
            brr[nn - 1] = NULL;
            if (strcmp("pinfo", brr[0]) == 0)
            {
                pin(brr, arg);
            }
            else
            {
                red(brr);
            }
            dup2(var, STDOUT_FILENO);
        }
    }
}