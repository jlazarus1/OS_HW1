//		commands.c
//********************************************
#include "commands.h"
#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>
#include<sys/wait.h>
#include <list>
#include<ctime>
#include<string>
#include <sys/types.h>
#include <signal.h>
#include <cstring>
#define SIGSTP 20


 bool job::getstopped() {

    return this->stopped;
}


void job::setstopped(bool boo) {
    this->stopped = boo;

}
int job::getId(){
        return this->jobId;

    }

    std::string  job::getjobstr(){
        return this->jobstr;
    }

    void job::setId(int id) {
    this->jobId = id;

}

void job::setstart_t(int time) {

    this->start_t = time;
}

int job::getstart_t() {

    return start_t;
}

void job::setstr(std::string str) {

   jobstr = str;
}

char *OLDCWD;

class history{
    std::queue <char*> queue;
    static history * inst;

    history(){};
public:
    history(history const&)         = default;
    void operator = (history const&) = delete;

    static history * getinst() {
        if(!inst)
            inst = new history;
        return  inst;

    }


    std::queue<char *> & getqueue() {
        return queue;
    }

};






history *history::inst = 0;
extern history *test = test ->getinst();



//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
int ExeCmd(std::list<job>& jobs, char* lineSize, char* cmdString)
{


    std::list<job>::iterator it;
	char *cmd = new char[MAX_LINE_SIZE];
    char *args[MAX_ARG];
	char pwd[MAX_LINE_SIZE];
	char* delimiters = " \t\n";  
	int i = 0, num_arg = 0;
	bool illegal_cmd = FALSE; // illegal command
	char* token = strtok(cmdString, delimiters);
	strcpy(cmd,token);
	if (cmd == NULL)
		return 0;
	while(token != NULL)
	{
       token = strtok(NULL, delimiters);
       if (token != NULL) {
           strcpy(args[i++], token);
       }
       else {
           args[i]=NULL;


       }
	}

    if(test->getqueue().size() < MAX_HISTORY) {
        char* tmp_str = strdup(lineSize);
        test->getqueue().push(tmp_str);
    }
    else {
        test->getqueue().pop();
        char* tmp_str = strdup(lineSize);
        test->getqueue().push(tmp_str);
    }

/*************************************************/
// Built in Commands PLEASE NOTE NOT ALL REQUIRED
// ARE IN THIS CHAIN OF IF COMMANDS. PLEASE ADD
// MORE IF STATEMENTS AS REQUIRED
/*************************************************/
	if (!strcmp(cmd, "cd") ) 
	{
	    const char *path = args[0];
        char *tmp;
        std::string hyph = "-";
        const char* d = hyph.c_str();
	    if (strcmp(path, d)==0)  // we should print and return the last path
        {
            char *buf;
            size_t size =0;
            buf = static_cast<char *>((void *) malloc(size));

            while (!getcwd(buf,size))
            {
                size = size+10;
                free(buf);
                buf = static_cast<char *>((void *) malloc(size));
            }
            chdir(OLDCWD);
            free(OLDCWD);
            OLDCWD = buf;
            std::cout << buf << '/n';
        }
	    else if (chdir(path) < 0)
        {
            illegal_cmd = TRUE;
            std::string str = " - path not found";
            const char* c = str.c_str();
            cmdString = strcat(cmdString,c);
        }





	} 
	
	/*************************************************/
	else if (!strcmp(cmd, "pwd"))
	{
		char *buf;
		size_t size =0;
		buf = static_cast<char *>((void *) malloc(size));

			while (!getcwd(buf,size))
			{
				size = size+10;
                free(buf);
                buf = static_cast<char *>((void *) malloc(size));
			}

			printf(buf);
			printf("\n");
			free(buf);



		
	}

	/*************************************************/
	
	else if (!strcmp(cmd, "jobs")) 
	{

    int i=1;
    for (it = jobs.begin(); it !=jobs.end(); it++)
    {

        int time = (int)std::time(nullptr);
        int runtime = time - it->getstart_t();
        if (it->getstopped()==false) {
            std::cout << "[" << i++ << "] " << it->getjobstr() << runtime << " secs\n";
        }
        else {

            std::cout << "[" << i++ << "] " << it->getjobstr() << runtime << " secs (Stopped)\n";
        }

    }

	}
	/*************************************************/
	else if (!strcmp(cmd, "showpid"))
	{
	    int pid = getpid();
	    std::cout<<"smash pid is "<<pid<<"\n";
		
	}
	/*************************************************/
	else if (!strcmp(cmd, "fg")) 
	{
		
	} 
	/*************************************************/
	else if (!strcmp(cmd, "bg")) 
	{
  		
	}
	/*************************************************/
	else if (!strcmp(cmd, "quit"))
	{
   		
	} 
	/*************************************************/
    else if (!strcmp(cmd, "history"))
    {
        std::queue<char*> copy;
        copy=test->getqueue();
        while(!copy.empty()){
            std::cout << copy.front() << '\n';
            copy.pop();
        }


    }
    /*************************************************/
    else if (!strcmp(cmd, "kill"))
    {

        if (args[2]!= NULL || args[1] == NULL || args[0] == NULL)
        {
            std::cout <<"error";
            return(-1);

        }

       std::string frstchar(args[0],1);
       std::string signum(args[0],strlen(args[0]));
       signum.erase(signum.begin());
       std::string loc(args[1],strlen(args[1]));
       std::string hyph("-",1);
       std::string::iterator strit;
       for (strit=loc.begin();strit!=loc.end();strit++)
       {
           if (!std::isdigit(*strit))
           {
               std::cout<<"not a number"<<"\n";
               return(-1);

           }

       }

        for (strit=signum.begin();strit!=signum.end();strit++)
        {
            if (!std::isdigit(*strit))
            {
                std::cout<<"not a number"<<"\n";
                return(-1);

            }

        }
       int isignum = std::stoi(signum);
       int iloc = std::stoi(loc);

       if (frstchar != hyph)
        {
            std::cout<<"syntax error"<<"\n";
            return (-1);
        }
        it= jobs.begin();
       if (iloc>jobs.size())
       {
           std::cout<<"error no such job"<<"\n";
           return(-1);
       }
        std::advance(it, iloc-1);
        if (kill(it->getId(), isignum)!= 0 )
        {

            std::cout<<"error sending signal"<<"\n";
            return(-1);
        }
        else {

            if (isignum == SIGSTOP || isignum == SIGSTP)
            {
                it->setstopped(true);
            }
            else if(isignum == SIGCONT)
            {
                it->setstopped(false);


            }
            else {
                return(0);
            }
        }
        return (0);



    }
    /*************************************************/
    else if (!strcmp(cmd, "cp"))
    {

    }
    /*************************************************/
    else if (!strcmp(cmd, "diff"))
    {

    }
    /*************************************************/

	else // external command
	{

 		ExeExternal(args, cmd,cmdString);
	 	return 0;
	}
	if (illegal_cmd == TRUE)
	{
		printf("smash error: > \"%s\"\n", cmdString);
		return 1;
	}
    return 0;
}
//**************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string
// Returns: void
//**************************************************************************************
void ExeExternal(char *args[MAX_ARG], char* cmd,char* cmdString)
{
	int pID;
	pID = fork();

        if (pID == 0) {

            std::cout<<"child"<<"\n";
            setpgrp();

            execv(cmd,args);
           // system("ls");

        }
        else
            {
                std::cout<<"test"<<"\n";
                wait(NULL);
            }

}

//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize, std::list<job>& jobs,char* cmdString)
{

   // sigset_t blockMask, orig_mask;
   // sigemptyset(&blockMask);
  //  sigaddset(&blockMask, SIGCHLD);
  //  sigprocmask(SIG_SETMASK, &blockMask, &orig_mask);

	char* Command;
	char* delimiters = " \t\n";
	char *args[MAX_ARG];
	int time;
	char* cmd;
    char pwd[MAX_LINE_SIZE];
    int i = 0, num_arg = 0;
    bool illegal_cmd = FALSE; // illegal command
    cmd = strtok(lineSize, delimiters);
    if (cmd == NULL)
        return 0;
    args[0] = cmd;
    for (i=1; i<MAX_ARG; i++)
    {
        args[i] = strtok(NULL, delimiters);
        if (args[i] != NULL)
            num_arg++;

    }





    if (cmdString[strlen(cmdString)-1] == '&')
	{
        cmdString[strlen(cmdString)-1] = '\0';
        int pID;
        pID = fork();

        if (pID == 0) {

            setpgrp();
            execv(cmd,args);
            exit(0);

        }
        else
        {

            time = (int)std::time(nullptr);
            std::string str;
            str = strtok(cmdString,delimiters);
            str.append(" : ");
            str.append(std::to_string(pID));
            str.append(" ");
            job tmp;
            tmp.setstart_t(time);
            tmp.setstr(str);
            tmp.setId(pID);
            jobs.push_front(tmp);


        }





		return 0;
	}
	else {
        return -1;
    }
}

