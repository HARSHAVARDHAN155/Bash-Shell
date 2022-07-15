#include <unistd.h>
#include <grp.h>
#include <signal.h>
#include <limits.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <sys/wait.h>
#include <err.h>
#include <errno.h>
#include <error.h>
#include <time.h>
#include <fcntl.h>
// #include "cd.c"
// #include "echo.c"
// #include "ls.c"
// #include "pinfo.c"

pid_t global;
char file_global[100];
int cd(char argument[1000], char home[1000],char cwd[1000]);
int echo(char *commads[1000],int s);
int ls(char cwd[1000] );
int only_l(char cwd[1000]);
int check_redirection(char arr[]);
int type(char arr[]);
int ls_a(char cwd[1000]);
void direction(char arr[],char *Arg);
void red_piping(char arr[],char *arg);
void red(char *arr[]);
int check_piping(char arr[]);
void piping(char arr[]);
void fg(char job_num[],int njobs);
int ls_ls(char cwd[1000]);
int pin(char **token, char *arg);
char bg[100][100];
void bg_bg(char job_num[],int njobs);
int bg_ids[100];
int bg_pids[100];
int bg_kills[100];