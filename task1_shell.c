#include <stdio.h>
#include <unistd.h>
#include <string.h>

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

        if(a[0] == 0) continue;

        if(strcmp(a[0],"cd")==0)
        {
            if(a[1]==0) chdir(getcwd(dir,50));
            else chdir(a[1]);
        }
    }

    return 0;
}

