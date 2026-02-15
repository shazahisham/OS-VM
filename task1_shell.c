#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    char in[50];
    char dir[50];
    char *a[10];

    while(1)
    {
        getcwd(dir,50);
        printf("%s> ",dir);
        fflush(stdout);

        fgets(in,50,stdin);
        in[strcspn(in,"\n")] = 0;

        int i=0;
        char *t = strtok(in," ");
        while(t){ a[i++] = t; t = strtok(NULL," "); }
        a[i] = 0;

        if(a[0]==0) continue;

        if(strcmp(a[0],"cd")==0)
        {
            if(a[1]==0) chdir(getcwd(dir,50));
            else chdir(a[1]);
        }
        else if(strcmp(a[0],"dir")==0)
        {
            char *d = a[1]?a[1]:".";
            DIR *dp = opendir(d);
            if(dp)
            {
                struct dirent *e;
                while((e=readdir(dp))!=0) printf("%s\n",e->d_name);
                closedir(dp);
            }
        }
        else if(strcmp(a[0],"echo")==0)
{
    int j=1;
    while(a[j]!=0)
    {
        printf("%s ",a[j]);
        j++;
    }
    printf("\n");
}
        else if(strcmp(a[0],"environ")==0)
{
    extern char **environ;
    char **e = environ;
    while(*e!=0)
    {
        printf("%s\n",*e);
        e++;
    }
}
        else if(strcmp(a[0],"set")==0)
{
    if(a[1]!=0 && a[2]!=0)
        setenv(a[1],a[2],1);
}
        else if(strcmp(a[0],"help")==0)
{
    printf("Supported commands:\n");
    printf("cd dir echo environ set help pause quit\n");
}
        else if(strcmp(a[0],"pause")==0)
{
    printf("Press Enter to continue...");
    getchar();
}
        else if(strcmp(a[0],"quit")==0)
{
    break;
}
else
{
    pid_t pid = fork();

    if(pid==0)
    {
        execvp(a[0],a);
    }
    else
    {
        wait(NULL);
    }
}
    }

    return 0;
}

