#include <stdio.h>
#include <unistd.h>

int main()
{
    char in[50];
    char dir[50];

    while(1)
    {
        getcwd(dir,50);
        printf("%s> ",dir);
        fflush(stdout);

        fgets(in,50,stdin);
    }

    return 0;
}

