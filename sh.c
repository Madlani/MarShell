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

  cwd = getcwd();

  printf("%s[%s]> ", prompt , cwd );


//----------------------------------------------------------------------------
    /* get command line and process */


    /* check for each built in command and implement */

    if (strcmp(command,"which") == 0){
      //fill in code for this command
    }

    else if (strcmp(command,"where") == 0){
      //fill in code for this command
    }

    else if (strcmp(command,"list") == 0){
      //fill in code for this command
    }

    else if (strcmp(command,"printenv") == 0){
      //fill in code for this command
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
    sprintf(cmd, "%s/gcc", pathlist->element);
    if (access(cmd, F_OK) == 0)
      printf("[%s]\n", cmd);
    pathlist = pathlist->next;
  }

   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */

}

char *environmentPath = getenv(PATH);

char *where(char *command, struct pathelement *pathlist )
{
  /* similarly loop through finding all locations of command */
  while (pathlist) 
  {
    sprintf(cmd, "%s/gcc", pathlist->element);
    if (access(cmd, F_OK) == 0)
      printf("[%s]\n", cmd);
    pathlist = pathlist->next;
  }
} 



void list ( char *dir )
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
} /* list() */

void exit (){
  exit(0);
}

void exec(){

}

void prompt(){
  
}
