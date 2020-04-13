//		commands.c
//********************************************
#include "commands.h"
#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>
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
int ExeCmd(void* jobs, char* lineSize, char* cmdString)
{



	char* cmd;
	char*args[MAX_ARG];
	char pwd[MAX_LINE_SIZE];
	char* delimiters = " \t\n";  
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
	    const char *path = args[1];
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
	else if (!strcmp(cmd, "mkdir"))
	{
 		
	}
	/*************************************************/
	
	else if (!strcmp(cmd, "jobs")) 
	{

	}
	/*************************************************/
	else if (!strcmp(cmd, "showpid")) 
	{
		
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
 		ExeExternal(args, cmdString);
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
void ExeExternal(char *args[MAX_ARG], char* cmdString)
{
	int pID;
    	switch(pID = fork()) 
	{
    		case -1: 
					// Add your code here (error)
					
					/* 
					your code
					*/
        	case 0 :
                	// Child Process
               		setpgrp();
					
			        // Add your code here (execute an external command)
					
					/* 
					your code
					*/
			
		//	default:
                	// Add your code here
					
					/* 
					your code
					*/
	}
}
//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char* lineSize)
{
	char ExtCmd[MAX_LINE_SIZE+2];
	char *args[MAX_ARG];
    if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) || (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&")))
    {
		// Add your code here (execute a complicated command)
					
		/* 
		your code
		*/
	} 
	return -1;
}
//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize, void* jobs)
{

	char* Command;
	char* delimiters = " \t\n";
	char *args[MAX_ARG];
	if (lineSize[strlen(lineSize)-2] == '&')
	{
		lineSize[strlen(lineSize)-2] = '\0';
		// Add your code here (execute a in the background)
					
		/* 
		your code
		*/
		
	}
	return -1;
}

