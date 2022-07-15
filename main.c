#include "cshell.h"

char cwd[1000];
char home[1000];
char host[1000];
char user[1000];

void bgkills()
{
    for (int i = 0; i < 100; i++)
    {
        bg_kills[i] = 0;
    }
}

char history[20][100];
int ctr = 0;

void kill_bg(char **args)
{
    long long int val = atoi(args[1]);
    long long int ki = atoi(args[2]);
    for (int i = 0; i < ctr; i++)
    {
        if (i + 1 == val && ki == 9)
        {
            kill(bg_pids[i], 9);
            bg_kills[i] = -1;
        }
    }
}

void print_bg(char **args, int num)
{
    char file_path[100];
    char line[300];
    if (num == 2)
    {
        for (int i = 0; i < ctr; i++)
        {
            if (bg_kills[i] != -1)
            {
                int count = 0;
                char proc_status;
                sprintf(file_path, "/proc/%d/stat", bg_pids[i]);
                FILE *ss;
                ss = fopen(file_path, "r");

                if (!(ss = fopen(file_path, "r")))
                {
                    // printf("[%d] closed %s [%d]\n", i + 1, bg[i], bg_pids[i]);
                }

                else
                {

                    int p;
                    char status;
                    long unsigned mem;
                    fscanf(ss, "%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &p, &status, &mem);
                    fclose(ss);
                    if (status == 'T' && strcmp(args[1], "-s") == 0)
                    {
                        printf("[%d] Stopped %s [%d]\n", i + 1, bg[i], bg_pids[i]);
                    }
                    else if (status != 'T' && strcmp(args[1], "-r") == 0)
                    {
                        printf("[%d] Running %s [%d]\n", i + 1, bg[i], bg_pids[i]);
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < ctr; i++)
        {
            if (bg_kills[i] != -1)
            {
                int count = 0;
                char proc_status;
                sprintf(file_path, "/proc/%d/stat", bg_pids[i]);
                FILE *ss;
                ss = fopen(file_path, "r");
                if (!(ss = fopen(file_path, "r")))
                {
                    // printf("[%d] closed %s [%d]\n", i + 1, bg[i], bg_pids[i]);
                }

                else
                {
                    int p;
                    char status;
                    long unsigned mem;
                    fscanf(ss, "%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &p, &status, &mem);
                    fclose(ss);
                    if (status == 'T')
                    {
                        printf("[%d] Stopped %s [%d]\n", i + 1, bg[i], bg_pids[i]);
                    }
                    else
                    {
                        printf("[%d] Running %s [%d]\n", i + 1, bg[i], bg_pids[i]);
                    }
                }
            }
        }
    }
}
void run_bg()
{
    int j, x, f;
    f = 0;
    pid_t pid = waitpid(-1, &x, WNOHANG);
    char str[100];
    if (pid != 0 && pid > 0)
    {

        for (j = 0; j < ctr; j++)
        {
            if (bg_pids[j] == pid)
            {
                strcpy(str, bg[j]);
                f = 1;
                break;
            }
        }
        if (WEXITSTATUS(x) == 0 && WIFEXITED(x) && f == 1)
        {
            printf("%s with %d exited normally\n", str, pid);
        }
    }
    return;
}

void process(int start, char **token, int num)
{
    int back = 0;
    int status;
    if (strcmp(token[num - 1], "&") == 0)
    {
        back = 1;
    }
    char **check_list;
    // int nn;
    if (back == 1)
    {
        int i = 0;
        for (int i = 0 + start; i < num - 1; i++)
        {
            check_list[i] = token[i];
            // printf("%s\n",token[i]);
        }
        check_list[i] = NULL;
    }
    else
    {
        int i = 0;
        for (int i = 0 + start; i < num; i++)
        {
            check_list[i] = token[i];
        }
        check_list[i] = NULL;
    }

    int pid;
    pid = fork();
    if (pid < 0)
    {
        printf("forking failed");
    }
    else if (pid == 0)
    {
        if (back == 1)
        {
            token[num - 1] = NULL;
            if (execvp(token[0 + start], token) == -1)
            {
                printf("Execution failed '%s'\n", token[0 + start]);
                return;
            }
        }
        else
        {
            if (execvp(token[0 + start], token) == -1)
            {
                printf("Execution failed '%s'\n", token[0 + start]);
                return;
            }
        }
        printf("%d", getpgrp());
    }
    else
    {

        if (back == 0)
        {
            int wpid;
            global = pid;
            strcpy(file_global, token[0]);
            // printf("[%d] \n",global);
            wpid = waitpid(pid, &status, WUNTRACED);

            if (WIFSTOPPED(status))
            {
                printf("%s with %d exited normally\n", token[0], pid);
            }
        }
        else
        {

            bg_pids[ctr] = pid;
            strcpy(bg[ctr], token[0]);
            printf("%d\n", bg_pids[ctr]);
            ctr++;
        }
    }
}

void commad_line(int var)
{
    printf("<%s@%s:", user, host);
    if (strlen(home) == strlen(cwd))
    {
        printf("~> ");
    }
    else if (strlen(home) > strlen(cwd))
    {
        printf("~%s> ", cwd);
    }
    else if (strlen(home) < strlen(cwd))
    {
        printf("~");
        int i = strlen(home);
        while (cwd[i] != '\0')
        {
            printf("%c", cwd[i]);
            i++;
        }
        printf("> ");
    }
}
int test = 0;
void ctrlc()
{
    // fflush(stdout);
    printf("\n");
    commad_line(0);
    fflush(stdout);
    test = 1;
    signal(SIGINT, ctrlc);
}
void ctrlz()
{
    if (global != -22222)
    {
        kill(global, SIGTSTP);
        bg_pids[ctr] = global;
        strcpy(bg[ctr], file_global);
        ctr++;
    }
    else
    {
        printf("NO foreground process\n");
    }
}

int main(int argc, char *argv[])
{
    global = -22222;
    void bgkills();

    char lastdir[500];
    gethostname(host, sizeof(host));
    getlogin_r(user, sizeof(user));

    char *line;
    char *args[100];
    char getline[1000];
    getcwd(home, sizeof(home));
    getcwd(lastdir, sizeof(lastdir));
    // commad_line(0);
    while (1)
    {
        run_bg();

        signal(SIGINT, ctrlc);
        signal(SIGTSTP, ctrlz);
        getcwd(cwd, sizeof(cwd));
        global = -22222;

        if (test != 1)
        {
            commad_line(0);
        }
        else
        {
            test = 0;
        }
        // run_bg();

        char str[100];
        char *ptr = fgets(str, sizeof(str), stdin);
        if (ptr == NULL)
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }
        int len = strlen(str);
        // printf("%d\n",len);
        if (len == 1)
        {
            // printf("\n");
            continue;
        }

        char *harsha[1000];

        char *token1 = strtok(str, ";");

        int z = 0;
        while (token1 != NULL)
        {
            harsha[z] = token1;
            token1 = strtok(NULL, ";");
            z++;

            //printf("Command: %s\n", token1);
        }
        harsha[z] = token1;

        for (int t = 0; t < z; t++)
        {
            if (check_piping(harsha[t]) && check_redirection(harsha[t]))
            {
                // printf("coming..\n");
                red_piping(harsha[t], argv[0]);
                // printf("returning 1");
                continue;
            }
            if (check_redirection(harsha[t]))
            {
                direction(harsha[t], argv[0]);
                continue;
            }
            if (check_piping(harsha[t]))
            {
                piping(harsha[t]);
                continue;
            }
            char *token = strtok(harsha[t], " \n\t");

            int i = 0;
            while (token != NULL)
            {

                args[i] = token;
                token = strtok(NULL, " \n\t;");
                i++;
            }
            int num = i;
            args[i] = token;
            int a = 0;
            int l = 0;
            int la = 0;
            char paths[1000][1000];
            char arr[1000];
            int size = 0;

            if (strcmp(args[0], "cd") == 0)
            {
                if (args[1] != NULL)
                {
                    if (strcmp(args[1], "-") == 0)
                    {
                        printf("%s\n", lastdir);
                        break;
                    }
                }
                strcpy(lastdir, cwd);
                cd(args[1], home, cwd);
            }
            else if (strcmp(args[0], "echo") == 0)
            {
                echo(args, 1);
            }
            else if (strcmp(args[0], "jobs") == 0)
            {
                print_bg(args, num);
            }
            else if (strcmp(args[0], "sig") == 0)
            {
                kill_bg(args);
            }
            else if (strcmp(args[0], "fg") == 0)
            {
                fg(args[1], ctr);
            }
            else if (strcmp(args[0], "bg") == 0)
            {
                bg_bg(args[1], ctr);
            }
            else if (strcmp(args[0], "pwd") == 0)
            {
                char buff[1000];
                getcwd(buff, sizeof(buff));
                printf("%s\n", buff);
            }
            else if (strcmp(args[0], "ls") == 0)
            {
                for (int j = 1; j < i; j++)
                {
                    if (strcmp(args[j], "-la") == 0 || strcmp(args[j], "-al") == 0)
                    {
                        la = 1;
                    }
                    else if (strcmp(args[j], "-l") == 0)
                    {
                        l = 1;
                    }
                    else if (strcmp(args[j], "-a") == 0)
                    {
                        a = 1;
                    }
                    else
                    {
                        strcpy(arr, args[j]);
                        strcpy(paths[size], arr);
                        // printf("%s\n",paths[size]);

                        size++;
                    }
                }
                if (size == 0)
                {
                    if (la == 1 || (a == 1 && l == 1))
                    {
                        // printf("%d",la);
                        ls(cwd);
                    }
                    else if (a == 1)
                    {
                        // printf("%d",la);
                        ls_a(cwd);
                    }
                    else if (l == 0)
                    {
                        // printf("%d",la);
                        ls_ls(cwd);
                    }
                    else if (l == 1)
                    {
                        // printf("%d", la);

                        only_l(cwd);
                    }
                }
                else
                {
                    // for (int k = 0; k < size; k++)
                    // {
                    //     printf("%d:%s..",k,paths[k]);
                    // }
                    // printf("\n");
                    char copy[1000];
                    strcpy(copy, cwd);
                    for (int i = 0; i < size; i++)
                    {
                        if (i > 0)
                        {
                            printf("\n\n");
                        }
                        if (size > 1)
                        {
                            printf("%s:\n", paths[i]);
                        }

                        int kk = cd(paths[i], home, cwd);
                        // DIR *di = opendir(cwd);
                        char dir[1000];
                        getcwd(dir, sizeof(dir));
                        if (kk != -1)
                        {
                            if (la == 1 || (a == 1 && l == 1))
                            {
                                // printf("%d",la);
                                ls(dir);
                                cd(copy, home, cwd);
                            }
                            else if (a == 1)
                            {
                                // printf("%d",la);
                                ls_a(dir);
                                cd(copy, home, cwd);
                            }
                            else if (l == 0)
                            {
                                // printf("%d", size);
                                ls_ls(dir);
                                cd(copy, home, cwd);
                            }
                            else if (l == 1)
                            {
                                // printf("%d", la);

                                only_l(dir);
                                cd(copy, home, cwd);
                            }
                        }
                    }
                }
            }
            else if (strcmp(args[0], "pinfo") == 0)
            {
                pin(args, argv[0]);
            }
            else if (strcmp(args[0], "repeat") == 0)
            {
                if (args[1] != NULL && args[2] != NULL)
                {
                    int n = atoi(args[1]);
                    for (int i = 0; i < n; i++)
                    {
                        if (strcmp(args[2], "cd") == 0)
                        {

                            cd(args[3], home, cwd);
                        }
                        else if (strcmp(args[2], "echo") == 0)
                        {
                            echo(args, 3);
                        }
                        else if (strcmp(args[2], "pwd") == 0)
                        {
                            char buff[1000];
                            getcwd(buff, sizeof(buff));
                            printf("%s\n", buff);
                        }

                        else if (strcmp(args[2], "pinfo") == 0)
                        {
                            pin(args, argv[0]);
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
            else if (strcmp(args[0], "exit") == 0)
            {
                exit(0);
            }

            else
            {
                process(0, args, num);
            }

            //token1 = strtok(NULL, ";");
        }
    }

    return 0;
}