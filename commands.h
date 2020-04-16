#ifndef _COMMANDS_H
#define _COMMANDS_H
#include <unistd.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <list>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LINE_SIZE 80
#define MAX_ARG 20
#define MAX_HISTORY 50

class job{
private:
    int jobId = 0;
    std::string jobstr;
    int start_t = 0;
    bool stopped = false;
public:
    bool getstopped();
    void setstopped(bool boo);
    int getId();
    int getstart_t();
    void setstart_t(int time);
    std::string getjobstr();
    void setId(int id);
    void setstr(std::string str);


};

typedef enum { FALSE , TRUE } boolean;
int ExeComp(char* lineSize);
int BgCmd(char* lineSize, std::list<job> & jobs,char* cmdString);
int ExeCmd(std::list<job> & jobs, char* lineSize, char* cmdString);
void ExeExternal(char *args[MAX_ARG], char* cmd,char* cmdString);
#endif

