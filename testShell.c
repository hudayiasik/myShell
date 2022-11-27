#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

char *readLine(){
	char *line = (char *)malloc(sizeof(char) * 1024); //  Buffer Allocation 
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
		else{
			line[pos] = read;
		}
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

int takeInput(char* str){
	char* buf;
	buf = readLine();
	if (strlen(buf) != 0) {
		strcpy(str, buf);
		return 0;
	} else return 1;
}

void processString(char *str, char **parsed){
	int i;
	for (i = 0; i < 100; i++)
	{
		parsed[i] = strsep(&str, " ");
		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
	}
}


int main(){
	char inputString[1000], *Args[100];
	while (1) {
		printf("myshell>>");
        if (takeInput(inputString))continue;
        processString(inputString,Args);
        printf("%s",Args[0]);


	}
	return 0;
}