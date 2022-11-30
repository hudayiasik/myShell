
#include <stdio.h>
#include <stdlib.h>

char* getSystemTime(){
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  return timeinfo;
}

int main(int argc, char* argv[]){
    printf(getSystemTime());
	if(argc==4){
		int num;
        FILE *fptr;

        fptr = fopen("file.txt", "a");
        if(fptr == NULL)
        {
            printf("Error!");   
            exit(1);             
        }
        fprintf(fptr,"%s  %d  %d \n",getSystemTime(),getpid(),getppid());
        fclose(fptr);

 		}else {
 			puts("Invalid arguments");
 			exit(1);
 		}
	exit(0);
	
}