#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <dirent.h> 
int takeInput(char* );
char* readLine();
void processString(char*, char**);
void clear();
void cat(char*);
void help();
void callPrograms(char* parsed[]);
void ls();
void callProgram(char* name,char* args[]);
int executeCommands(char**);

int main(){
	char inputString[1000], *Arguments[100];
	while (1) {
		printf("myshell>>");
        if (takeInput(inputString))continue;
        processString(inputString,Arguments);
		executeCommands(Arguments);
	}
	return 0;
}

int i; 
int takeInput(char* str){
	char* buf;
	buf = readLine();
	if (strlen(buf)!= 0){
		strcpy(str, buf);
		return 0;
	}else 
		return 1;
}
char *readLine(){
	char* line = (char *)malloc(sizeof(char) * 1024); //  Buffer Allocation 
	char read;
	int pos = 0 ;
	char nullChar = '\0';
	int bufferSize = 1024;
	char newLine = '\n';
	if (!line){ // Fail
		printf("\n Buffer Could Not Allocated.");
		exit(1); 
	}

	while(1){
		read=getchar();
		if (read == EOF || read == newLine){
			line[pos] = nullChar;
			return line;
		}
		else
			line[pos] = read;
		
		pos ++;
		// If the buffer exceeded 
		if (pos >= bufferSize){
			bufferSize += 1024;
			line = realloc(line, sizeof(char) * bufferSize);
			if (!line){ // Fail
			printf("\nBuffer Could Not Allocated");
			exit(1); 
			}
		}
	}

}

void processString(char *str, char **parsed){
	for (i=0; i < 100; i++){
		parsed[i] = strsep(&str, " ");
		if (parsed[i] == NULL)break;
		if (strlen(parsed[i]) == 0)i--;
	}
}
//_______________	COMMANDS________________________

void clear(){
	printf("\033[H\033[J");
}
void cat(char *str){
	printf("cat: %s\n",str);
}
// Help command
void help(){
	puts("\nCommand list ..."
		 "\n>exit -- exits program "
		 "\n>ls -- lists files"
		 "\n>exit -- exists from current program"
		 "\n>clear -- Clear Screen"
		 "\n>cat -- Custom program to repeat a string"
		 "\n>bash -- Opens actual bash terminal");

	return;
}
void bash(){
	printf("hello");
	pid_t pid = fork();
	if (pid == -1) {
		printf("\nFailed to fork");
		return;
	} else if (pid == 0) {
		system("/bin/bash");	
		exit(0);
	} else {
		wait(NULL);
		return;
	}

}
void callProgram(char* name,char* args[]){
	int f,e;
  	f = fork(); //Çalışan processin kopyasını oluşturmak için fork işlemini gerçekleştirdim.
        if(f == 0){  //Child proses ise
            e = execv(name,args); //Ayrı programı çalıştırmak için execv kullandım.
            perror("execv failed \n");
            }		
}
void callPrograms(char* parsed[]){
	pid_t pid = fork();
	if (pid == -1){
		printf("Failed to fork\n");
		return;
	}
	else if (pid == 0){
		if (execvp(parsed[0], parsed) < 0){
			printf("%s Invalid command..\n",parsed[0]);
		}
		exit(0);
	}
	else{
		// waiting for child to abort
		wait(NULL);
		return;
	}
}

void ls(){
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
  return(0);
}

//__________________________________________________



int executeCommands(char **parsed){
	int commandCount = 8;
	int indicator = 0;	   //0      1       2       3    4     5       6      7
	char* commandList[]= {"exit","bash","clear","ls","cat","execx","writef","help"};
	
	for (i = 0; i < sizeof(commandList);i++){
		if(strcmp(parsed[0], commandList[i]) == 0)break; //identify and mach command

	}
	printf("%d \n",i);

	switch (i){
		case 0:exit(0);break;
		case 1:bash();break;
		case 2:clear();break;
		case 3:ls();break;
		case 4:cat(parsed[1]);break;
		case 5:callPrograms(parsed);break;//exec
		case 6:callPrograms(parsed);break;//writef
		case 7:help();break;
		default: printf("invalid argument \n");break;
	}
}



