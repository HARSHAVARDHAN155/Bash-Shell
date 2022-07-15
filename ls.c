#include "cshell.h"

int ls_ls(char cwd[1000])
{
    struct dirent *de;

    DIR *dir = opendir(cwd);

    if (dir == NULL)
    {
        return 0;
    }

    while ((de = readdir(dir)) != NULL)
    {
        if (de->d_name[0] != '.') // without hidden files
        {
            printf("%s\n", de->d_name);
        }
    }
    closedir(dir);
    return 0;
}

int ls_a(char cwd[1000])
{
    struct dirent *de;

    DIR *dir = opendir(cwd);

    if (dir == NULL)
    {
        return 0;
    }

    while ((de = readdir(dir)) != NULL)
    {

        printf("%s\n", de->d_name);
    }
    closedir(dir);
    return 0;
}

int ls(char cwd[1000])
{

    struct dirent *de;
    struct dirent *di;

    DIR *dir = opendir(cwd);

    if (dir == NULL)
    {
        return 0;
    }
    char file_name[1000]; /* code */
    struct stat mystat;
    long total = 0;

    while ((di = readdir(dir)) != NULL)
    {
        strcpy(file_name, di->d_name);
        stat(file_name, &mystat);
        // printf("%ld\n", mystat.st_blocks);
        total += mystat.st_blocks;
    }
    closedir(dir);
    printf("total %ld\n", total / 2);
    dir = opendir(cwd);
    if (dir == NULL)
    {
        return 0;
    }

    while ((de = readdir(dir)) != NULL)
    {

        char buff[100];
        strcpy(file_name, de->d_name);
        stat(file_name, &mystat);
        printf((S_ISDIR(mystat.st_mode)) ? "d" : "-");
        printf((mystat.st_mode & S_IRUSR) ? "r" : "-");
        printf((mystat.st_mode & S_IWUSR) ? "w" : "-");
        printf((mystat.st_mode & S_IXUSR) ? "x" : "-");
        printf((mystat.st_mode & S_IRGRP) ? "r" : "-");
        printf((mystat.st_mode & S_IWGRP) ? "w" : "-");
        printf((mystat.st_mode & S_IXGRP) ? "x" : "-");
        printf((mystat.st_mode & S_IROTH) ? "r" : "-");
        printf((mystat.st_mode & S_IWOTH) ? "w" : "-");
        printf((mystat.st_mode & S_IXOTH) ? "x" : "-");
        printf(" ");
        printf("%ld ", mystat.st_nlink);
        struct passwd *pw = getpwuid(mystat.st_uid);
        struct group *gr = getgrgid(mystat.st_gid);
        printf("%s ", gr->gr_name);
        printf("%s ", pw->pw_name);
        printf("%ld ", mystat.st_size);
        strftime(buff, 100, "%b %d %H:%M", localtime(&mystat.st_mtime));
        printf("%s ", buff);
        // printf("%ld \t", mystat.st_blocks);
        printf("%s\n", de->d_name);
    }
    closedir(dir);
    return 0;
}

int only_l(char cwd[1000])
{
    {

        struct dirent *de;

        DIR *dir = opendir(cwd);
        long total =0;

        if (dir == NULL)
        {
            return 0;
        }
        char file_name[1000]; /* code */
        struct stat mystat;

        while ((de = readdir(dir)) != NULL)
        {
            if (de->d_name[0] != '.') // without hidden files
            {
                strcpy(file_name, de->d_name);
                stat(file_name, &mystat);
                // printf("%ld\n", mystat.st_blocks);
                total += mystat.st_blocks;
            }
        }
        closedir(dir);
        printf("total %ld\n", total / 2);
        dir = opendir(cwd);
        if (dir == NULL)
        {
            return 0;
        }

        while ((de = readdir(dir)) != NULL)
        {
            if (de->d_name[0] != '.') // without hidden files
            {
                char buff[100];
                strcpy(file_name, de->d_name);
                stat(file_name, &mystat);
                printf((S_ISDIR(mystat.st_mode)) ? "d" : "-");
                printf((mystat.st_mode & S_IRUSR) ? "r" : "-");
                printf((mystat.st_mode & S_IWUSR) ? "w" : "-");
                printf((mystat.st_mode & S_IXUSR) ? "x" : "-");
                printf((mystat.st_mode & S_IRGRP) ? "r" : "-");
                printf((mystat.st_mode & S_IWGRP) ? "w" : "-");
                printf((mystat.st_mode & S_IXGRP) ? "x" : "-");
                printf((mystat.st_mode & S_IROTH) ? "r" : "-");
                printf((mystat.st_mode & S_IWOTH) ? "w" : "-");
                printf((mystat.st_mode & S_IXOTH) ? "x" : "-");
                printf(" ");
                printf("%ld ", mystat.st_nlink);
                struct passwd *pw = getpwuid(mystat.st_uid);
                struct group *gr = getgrgid(mystat.st_gid);
                printf("%s ", gr->gr_name);
                printf("%s ", pw->pw_name);
                printf("%ld ", mystat.st_size);
                strftime(buff, 100, "%b %d %H:%M", localtime(&mystat.st_mtime));
                printf("%s ", buff);
                // printf("%ld ",mystat.st_blksize);har
                printf("%s\n", de->d_name);
            }
        }
        closedir(dir);
        return 0;
    }
}