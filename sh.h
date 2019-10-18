#include "get_path.h"

int pid;
int sh( int argc, char **argv, char **envp);
char *which(char *command, struct pathelement *pathlist);
char *where(char *command, struct pathelement *pathlist);
void list ( char *dir );
void printenv(char **envp);

//void exitShell ();
void exec();
void prompt();
char **inputToArray(char *input, char **argv, int *argsCount);
void cd(char* cdLoc);

int getInput(char *strBuffer);

#define PROMPTMAX 32
#define MAXARGS 10
#define BUFFERSIZE 256