/*	smash.c
main file. This file contains the main function of smash
*******************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "commands.h"
#include "signals.h"
#include<queue>
#include<list>
#include<ctime>
#include<string>

#define MAX_LINE_SIZE 80

using namespace std;

std::list<job> jobs;
void sigchld_handler(int signum)
{
   pid_t pid = wait(NULL);
    std::list<job>::iterator it;

    for (it = jobs.begin(); it!=jobs.end(); it++){
        if (it->getId() == pid)
        {
            jobs.erase(it--);
        }


    }
    std::cout<<"child died: " << pid << "\n";





}





char* L_Fg_Cmd;
//void* jobs = NULL; //This represents the list of jobs. Please change to a preferred type (e.g array of char*)


char lineSize[MAX_LINE_SIZE]; 
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = &sigchld_handler;
    sigaction(SIGCHLD,&act,NULL);

    std::queue<char*> hist;
    char cmdString[MAX_LINE_SIZE]; 	   


	//signal declaretions
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.c
	 /* add your code here */
	
	/************************************/
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.c
	//set your signal handlers here
	/* add your code here */

	/************************************/

	/************************************/
	// Init globals

	L_Fg_Cmd =(char*)malloc(sizeof(char)*(MAX_LINE_SIZE+1));
	if (L_Fg_Cmd == NULL) 
			exit (-1); 
	L_Fg_Cmd[0] = '\0';
	
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    	while (1)
        {
	 	printf("smash > ");
		fgets(lineSize, MAX_LINE_SIZE, stdin); // reads a line from the input stdin to lineSize
		strcpy(cmdString, lineSize);    	// copies the line to cmdString
		cmdString[strlen(lineSize)-1]='\0';
		//std::cout<<std::time(nullptr)<<"\n";
					// background command	
	 	if(BgCmd(lineSize, jobs,cmdString)==0) continue; // a function in commands.c executes a background command.
					// built in commands
		ExeCmd(jobs, lineSize, cmdString);  // a function in commands.c executes and interprets a built in command
		
		/* initialize for next line read*/
		lineSize[0]='\0';
		cmdString[0]='\0';
	}
#pragma clang diagnostic pop
    return 0;
}
#pragma clang diagnostic pop

