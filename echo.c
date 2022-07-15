#include "cshell.h"

int echo(char **commads,int start)
{
    for (int i = start; i < sizeof(commads) && commads[i]!=NULL; i++)
    {
        printf("%s ",commads[i]);
    }
    printf("\n");
    
}