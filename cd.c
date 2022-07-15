#include "cshell.h"

int cd(char command[1000], char home[1024], char cwd[1000])
{
    char hdir[1024];
    char buff[1000];
    // strcpy(lastdir,cwd);
    getcwd(buff, sizeof(buff));
    strcpy(hdir, cwd);
    int ret;
    if (command == NULL)
    {
        ret = chdir(home);
    }
    else if (strcmp(command, "~") == 0)
    {
        ret = chdir(home);
    }
    else
    {
        ret = chdir(command);
    }
    if (ret != 0)
    {
        perror("failed");
        return -1;
    }
    // char arr[500];
    // getcwd(arr,500);
	// if(strcmp(arr,predir)!=0){
	// 	strcpy(lastdir,predir);
	// 	strcpy(predir,arr);
	// }
    return 1;
}