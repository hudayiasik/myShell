
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

        printf("%s, %s, %s, %s,  ",argv[0],argv[1],argv[2],argv[3]);
        fptr = fopen("test.txt", "a"); //şimdilik test.txt
        if(fptr == NULL)
        {
            printf("Error!");   
            exit(1);             
        }
        fprintf(fptr,"%d",getpid());
        fclose(fptr);

 		}else {
 			puts("Invalid arguments");
 			exit(1);
 		}
	exit(0);
	
}