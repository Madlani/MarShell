#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"

int sh( int argc, char **argv, char **envp )
{
  char *prompt = calloc(PROMPTMAX, sizeof(char));
  char *commandline = calloc(MAX_CANON, sizeof(char));
  char *command, *arg, *commandpath, *p, *pwd, *owd;
  char **args = calloc(MAXARGS, sizeof(char*));
  int uid, i, status, argsct, go = 1;
  struct passwd *password_entry;
  char *homedir;
  struct pathelement *pathlist;

  uid = getuid();
  password_entry = getpwuid(uid);               /* get passwd info */
  homedir = password_entry->pw_dir;		/* Home directory to start
						  out with*/
     
  if ( (pwd = getcwd(NULL, PATH_MAX+1)) == NULL )
  {
    perror("getcwd");
    exit(2);
  }
  owd = calloc(strlen(pwd) + 1, sizeof(char));
  memcpy(owd, pwd, strlen(pwd));
  prompt[0] = ' '; prompt[1] = '\0';

  /* Put PATH into a linked list */
  pathlist = get_path();

  while ( go )
  {

//----------------------------------------------------------------------------

/* print your prompt */

  char *cwd = getcwd(NULL, 0);

  printf("%s[%s]> ", prompt , cwd );
  getInput(commandline);
  //use strtok to break into array, then select the [0]

  args = inputToArray(commandline, argv, argc);


//----------------------------------------------------------------------------
    /* get command line and process */


    /* check for each built in command and implement */
//----------------------------------------------------------------------------
//Done commands!!!

//----------------------------------------------------------------------------

    if (strcmp(args[0],"which") == 0){
      which(args[1], pathlist);
      //fill in code for this commandline
    }

    else if (strcmp(args[0],"where") == 0){
      where(args[1], pathlist);
      //fill in code for this commandline
    }

    else if (strcmp(args[0],"cd") == 0){
      cd(args[1]);
        }

    else if (strcmp(args[0],"pwd") == 0){
      //fill in code for this commandline
    }

    else if (strcmp(args[0],"list") == 0){
    printf("list command");

      //fill in code for this commandline
    }

    else if (strcmp(args[0],"pid") == 0){
      //fill in code for this commandline
    }

    else if (strcmp(args[0],"kill") == 0){
      //fill in code for this commandline
    }

    else if (strcmp(args[0],"printenv") == 0){
      printf("printenv command");
      //fill in code for this commandline
    }

    
    else if (strcmp(args[0],"exit") == 0){
      printf("exit command");
      go = 0;
    }

    else{
      //code for exec
    }


//----------------------------------------------------------------------------
     /*  else  program to exec */
    {
       /* find it */
       /* do fork(), execve() and waitpid() */

      /* else */
        /* fprintf(stderr, "%s: Command not found.\n", args[0]); */
    }
  }
  return 0;
} /* sh() */


//-----------------------------------------------------------------------------
//Commands below

char *which(char *command, struct pathelement *pathlist )
{
  char *tmpCmd = malloc(256 * sizeof(char*));
  struct pathelement *tmpPath = pathlist;
  strcpy(tmpCmd, command);
  while (pathlist) 
  {
    if (command != NULL)
    {
      sprintf(tmpCmd, "%s/%s", pathlist->element, command);
      if (access(tmpCmd, F_OK) == 0)
      {
        printf("%s\n", tmpCmd);
        char *tmp = tmpCmd;
        free(tmpCmd);
        return tmp;
      }
      else if (access(tmpCmd, F_OK) != 0 && tmpPath -> next == NULL){
        free(tmpCmd);
        break;
      }
    tmpPath = tmpPath->next;

    }

    else{
      return NULL;
    }     

  }

   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */

}

//char *environmentPath = getenv(PATH);

char *where(char *command, struct pathelement *pathlist )
{
  /* similarly loop through finding all locations of command */
  while (pathlist) 
  {
    sprintf(command, "%s/gcc", pathlist->element);
    if (access(command, F_OK) == 0)
      printf("[%s]\n", command);
    pathlist = pathlist->next;
  }
} 



void list ( char *dir )
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
} /* list() */



void exec(){

}

void prompt(){
  
}

//If length isn't used, scrap it.
int getInput(char *strBuffer){
  int length = 0;
  if (fgets(strBuffer, BUFFERSIZE, stdin)!= 0){
    length = strlen(strBuffer);
    strBuffer[length - 1] = '\0';
  } 
  return length;
}

char **inputToArray(char *input, char **argv, int argsCount){
  int count = 0;
  char buff[BUFFERSIZE] = "";
  strcpy(buff, input);

  char *temp = strtok(buff, " ");

  while(strtok(NULL, " ")){
    count++;
  }

  argv = malloc((count+1)*sizeof(char *));
  argv[count] = NULL;

  count = 0;
  strcpy(buff, input);

  temp = strtok(buff, " ");

  while (temp){
    int len = strlen(temp);
    argv[count] = (char *)malloc((len + 1) * sizeof(char *));
    strcpy(argv[count], temp);
    count++;
    argsCount = count;
    temp = strtok(NULL, " ");
    }
    return argv;


}

void cd(char* cdLoc){
  struct passwd *password_entry;
  char* homedir;
  int uid = getuid();
  password_entry = getpwuid(uid);               /* get passwd info */
  homedir = password_entry->pw_dir;

  char *cwd = getcwd(NULL, 0);

  if (cdLoc == ""){
    chdir(password_entry->pw_dir);
  }
  // else if (cdLoc == "-"){
  //   char* prevDir = pwd
  //   chdir("-");
  // }
  else{
    strcat(cwd, "/");
    strcat(cwd, cdLoc);
    chdir(cwd);
  }


}
