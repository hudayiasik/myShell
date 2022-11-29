#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


// 0       1  2   3     4  5  
// execve -t 5  writef -f isim 
int main(int argc, char* argv[])
{
    int i;

    if(strcmp(argv[1],"-t")!=0){
        printf("wrong argument\n");
        exit(1);
    }
    if(strcmp(argv[3],"writef")!=0){
        printf("wrong argument\n");
        exit(1);
    }
    for (i = 0; i < atoi(argv[2]); i++)
    {
        pid_t pid;
        pid = fork();
        printf("fork\n");
        if (pid == -1){
            printf("fork eror\n");
            exit(0);

        }else if ( pid == 0){
            printf("0\n");
            char *writefArgs = {argv[4], argv[5]};
            execv(argv[3],writefArgs);

        }else {
            wait(&pid);
            printf("%d \n",i);

        }
        
    }

    return 0;
}