//Reggie Barnett
//Project 5
//My Shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char delim[10] = " \n\t()<>|&;"; //Delimiters for strtok 

int countArgs(char *); //Count Arguments

int main(){
	char cmdbuf[256];	//Buffer for fgets
	char cmdin[256]; //Untokenized command
	char *command; //Tokenized command
	int pid;
	int args;
	char **arg_array;
	int status = 0;
	int count;
	char *path = "";
	char *process;
	//Done declaring variables
	printf("\nNow running MyShell:\n\n");
	while(1) //Shell keeps running until you exit
	{
		printf("MyShell => ");
		fgets(cmdbuf,256,stdin);
		strcpy(cmdin,cmdbuf); //Copying input for later use
		args = countArgs(cmdbuf);
		arg_array = malloc(sizeof(char)*(args+1));
		count = 0;
		command = strtok(cmdbuf,delim);
		while(command != NULL) //Tokenizing the command
		{
			arg_array[count] = (char*)malloc(sizeof(char)*strlen(command));
			strcpy(arg_array[count],command);
			command = strtok(NULL,delim);
			count++;
		}
		if(strcmp(arg_array[0],"exit") == 0) //Exit shell
		{
			exit(1);
		}
		else if(strcmp(arg_array[0],"cd") == 0) //Change directory
		{
			chdir(arg_array[1]);
		}
		else //Other commands
		{
			pid = fork();
			if(pid != 0)
			{
				wait(&status);
				if(status != 0)
				{
					exit(0);
				}
			}
			else
			{
				process = malloc(sizeof(char)*(strlen(arg_array[0]+strlen(path))));
				process = strcat(strcpy(process, path),arg_array[0]);
				if(strstr(cmdin,">>") != NULL) //Appending
				{
					freopen(arg_array[count-1],"a",stdout);
					free(arg_array[count-1]);
					arg_array[count-1] = NULL;
				}
				else if(strstr(cmdin,">") != NULL) //Writing
				{
					freopen(arg_array[count-1],"w",stdout);
					free(arg_array[count-1]);
					arg_array[count-1] = NULL;
				}
				else if(strstr(cmdin,"<") != NULL) //Reading
				{
					freopen(arg_array[count-1],"r",stdin);
					free(arg_array[count-1]);
					arg_array[count-1] = NULL;
				}
				if(execvp(process,arg_array)<0) //Running command
				{
					printf("Exec failed\n");
				}
			}
		}
	}
	return 0;
}
int countArgs(char *buffer)
{
	int count = 0;
	char *cmd;
	char cmdbuffer[256];
	strcpy(cmdbuffer, buffer);
	cmd = strtok(cmdbuffer,delim);
	while(cmd != NULL)
	{
		cmd = strtok(NULL,delim);
		count++;
	}
	return count;
}