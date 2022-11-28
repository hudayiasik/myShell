#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
char *readLine()
{
	char *line = (char *)malloc(sizeof(char) * 1024); //  Buffer Allocation
	char read;
	int pos = 0;
	char nullChar = '\0';
	int bufferSize = 1024;
	char newLine = '\n';

	if (!line)
	{ // Fail
		printf("\n Buffer Could Not Allocated.");
		exit(1);
	}
	while (1)
	{
		read = getchar();
		if (read == EOF || read == newLine)
		{
			line[pos] = nullChar;
			return line;
		}
		else
		{
			line[pos] = read;
		}
		pos++;
		// If the buffer exceeded
		if (pos >= bufferSize)
		{
			bufferSize += 1024;
			line = realloc(line, sizeof(char) * bufferSize);
			if (!line)
			{ // Fail
				printf("\nBuffer Could Not Allocated");
				exit(1);
			}
		}
	}
}
// Input Function
int takeInput(char *str)
{
	char *buf;
	buf = readLine();
	if (strlen(buf) != 0)
	{
		strcpy(str, buf);
		return 0;
	}
	else
		return 1;
}
// Clear Function
void Clear()
{
	printf("\033[H\033[J");
}

// Echo Function
void Echo(char *str)
{
	printf("\nEcho : %s", str);
}
// Command Execution by file name
void callWithFileName(char **parsed)
{
	// Child process
	pid_t pid = fork();

	if (pid == -1)
	{
		printf("\nFailed to fork");
		return;
	}
	else if (pid == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nInvalid command..");
		}
		exit(0);
	}
	else
	{
		// waiting for child to abort
		wait(NULL);
		return;
	}
}

// Help command
void Help()
{
	puts("\nCommands to use ..."
		 "\n>echo -- prints arguments "
		 "\n>ls -- lists files"
		 "\n>exit -- exists from current program"
		 "\n>clear -- Clear Screen"
		 "\n>tekrar -- Custom program to repeat a string"
		 "\n>bash -- Opens actual bash terminal");

	return;
}

// Function to execute builtin commands
int commandExecution(char **parsed)
{
	int NumberOfCommands = 8;
	int i;
	int indicator = 0;
	char *ListOfCommands[NumberOfCommands];

	ListOfCommands[0] = "exit";
	ListOfCommands[1] = "echo";
	ListOfCommands[2] = "help";
	ListOfCommands[3] = "clear";
	ListOfCommands[4] = "ls";
	ListOfCommands[5] = "bash";
	ListOfCommands[6] = "cat";	  //--------------
	ListOfCommands[7] = "writef"; //-------------

	for (i = 0; i < NumberOfCommands; i++)
	{
		if (strcmp(parsed[0], ListOfCommands[i]) == 0)
		{
			indicator = i + 1;
			break;
		}
	}

	switch (indicator)
	{
	case 1:
		exit(0);
	case 2:
		Echo(parsed[1]);
		return 1;
	case 3:
		Help();
		return 1;
	case 4:
		Clear();
		return 1;
	case 5:
		callWithFileName(parsed);
		return 1;
	case 6:
		callWithFileName(parsed);
		return 1;
	case 7:
		Tekrar(parsed);
		return 1;
	case 8:
		writef(parsed);
		return 1;
	default:
		puts("Invalid Command");
		break;
	}

	return 0;
}

void processString(char *str, char **parsed)
{

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

int main(void)
{
	char inputString[1000], *Args[100];

	while (1)
	{
		printf("myshell>>");
		if (takeInput(inputString))
			continue;
		processString(inputString, Args);
		commandExecution(Args);
	}
	return 0;
}
