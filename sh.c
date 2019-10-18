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

    if (strcmp(args[0],"which") == 0){
      printf("which command");
      //fill in code for this commandline
    }

    else if (strcmp(args[0],"where") == 0){
      printf("where command");

      //fill in code for this commandline
    }

    else if (strcmp(args[0],"list") == 0){
    printf("list command");

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
  while (pathlist) 
  {     
    sprintf(command, "%s/gcc", pathlist->element);
    if (access(command, F_OK) == 0)
      printf("[%s]\n", command);
    pathlist = pathlist->next;
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
