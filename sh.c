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

int sh(int argc, char **argv, char **envp)
{
  char *command, *arg, *commandpath, *p, *pwd, *owd;
  int i, status, argsct;

  //Using these variables---------------------------------------------
  char *commandline = calloc(MAX_CANON, sizeof(char)); //commandline, read in & split into args
  char **args;                                         //array of commandline split into its parts
  int argsCount;                                       //going to be size of the args array, used in cd

  struct pathelement *pathlist; //used in which/where to see if built in commands are there
  pathlist = get_path();        /* Put PATH into a linked list */

  int uid; //used below to get the homedir set
  struct passwd *password_entry;
  char *homedir;
  uid = getuid();
  password_entry = getpwuid(uid);   /* get passwd info */
  homedir = password_entry->pw_dir; /* Home directory to start out with*/

  if ((pwd = getcwd(NULL, PATH_MAX + 1)) == NULL)
  {
    perror("getcwd");
    exit(2);
  }

  char *prompt = calloc(PROMPTMAX, sizeof(char)); //gets printed every line, change with "prompt" command
  prompt[0] = ' ';
  prompt[1] = '\0';

  owd = calloc(strlen(pwd) + 1, sizeof(char));
  memcpy(owd, pwd, strlen(pwd));

  int go = 1; //used to loop, exit changed this to 0
  while (go)
  {

    //----------------------------------------------------------------------------

    /* print your prompt */

    char *cwd = getcwd(NULL, 0);

    printf("%s[%s]>", prompt, cwd);

    getInput(commandline);

    //use strtok to break into array, then select the [0]
    //passing in the commandline to split, the x, and the argsCount to be updated
    args = inputToArray(commandline, argv, &argsCount);
    for (int i = 0; i < argsCount; i++)
    {
      printf("args[%d] = %s\n", i, args[i]);
    }
    command = args[0];
    //printf("%s\n",args[0]);
    //printf("%s\n",args[1]);
    //----------------------------------------------------------------------------
    /* get command line and process */

    /* check for each built in command and implement */
    //----------------------------------------------------------------------------
    //Done commands!!!

    //----------------------------------------------------------------------------

    //printf("%d\n",strcmp("hi", "hi"));
    //printf("%s\n",args[0]);

    if (strcmp(args[0], "which") == 0)
    {
      which(args[1], pathlist);
      //fill in code for this commandline
    }

    else if (strcmp(args[0], "where") == 0)
    {
      where(args[1], pathlist);
      //fill in code for this commandline
    }

    else if (strcmp(args[0], "cd") == 0)
    {
      //int argsCount = sizeof(args)/sizeof(char**);
      //printf("%s", "entering cd");

      if (argsCount == 1)
      {
        chdir(homedir);
      }

      else if (argsCount == 2)
      {
        if (strcmp(args[1], "-") == 0)
        {
          //go to preious dir
        }
        else if (strcmp(args[1], "..") == 0)
        {
          chdir("..");
        }
        else
        {
          chdir(args[1]);
        }
      }
    }

    else if (strcmp(args[0], "pwd") == 0)
    {
      //fill in code for this commandline
    }

    else if (strcmp(args[0], "list") == 0)
    {
      printf("list command");
      //fill in code for this commandline
    }

    else if (strcmp(args[0], "pid") == 0)
    {
      printf("%s %ld\n", "PID: ", (long)getpid());
      //fill in code for this commandline
    }

    else if (strcmp(args[0], "kill") == 0)
    {
      //fill in code for this commandline
    }

    else if (strcmp(args[0], "printenv") == 0)
    {
      printf("printenv command");
      //fill in code for this commandline
    }

    else if (strcmp(args[0], "prompt") == 0)
    {
      if (argsCount == 2)
      {
        prompt = args[1];
      }
      else
      {
        printf("Please provide a prompt: ");
        getInput(prompt);
      }
    }

    else if (strcmp(args[0], "exit") == 0)
    {
      printf("exit command\n");
      go = 0;
    }

    /*
    else{
      printf("command not found\n");
      }
    */
    //----------------------------------------------------------------------------
    /*  else  program to exec */
    else 
    {
      /* find it */
      /* do fork(), execve() and waitpid() */
      char *absPath = where(args[0], pathlist);
      if (absPath == NULL)
      {
        printf("YOUR COMMAND [%s]IS NOT FOUND. PLEASE ENTER A VALID COMMAND.\n", args[0]);
        //free(absPath);
      }
      else
      {
        pid = fork();
        if (pid == 0)
        {
          execve(absPath, args, envp);
          printf("ERROR: EXIT");
          exit(1);
        }
        else
        {
          waitpid(pid, NULL, 0);
        }
      }
      //      free(absPath);

      /* else */
      /* fprintf(stderr, "%s: Command not found.\n", args[0]); */
    }
  }

  for(int i  = argsCount - 1; i >= 0; i--){
    free(args[i]);
  }
  free(args);
  free(prompt);
    return 0;
  }
//} /* sh() */

//-----------------------------------------------------------------------------
//Done Commands below

char *where(char *command, struct pathelement *pathlist)
{
  char *tmpCmd = malloc(256 * sizeof(char *));
  struct pathelement *tmpPath = pathlist;
  strcpy(tmpCmd, command);
  while (pathlist)
  {
    if (command != NULL)
    {
      sprintf(tmpCmd, "%s/%s", tmpPath->element, command);
      if (access(tmpCmd, F_OK) == 0)
      {
        printf("%s\n", tmpCmd);
        char *tmp = tmpCmd;
        free(tmpCmd);
        return tmp;
      }
      else if (access(tmpCmd, F_OK) != 0 && tmpPath->next == NULL)
      {
        free(tmpCmd);
        break;
      }
      tmpPath = tmpPath->next;
    }
  }
  //free(tmpCmd);
  return NULL;
}

char *which(char *command, struct pathelement *pathlist)
{
  char *tmpCmd = malloc(256 * sizeof(char *));
  struct pathelement *tmpPath = pathlist;
  strcpy(tmpCmd, command);
  while (pathlist)
  {
    if (command != NULL)
    {
      sprintf(tmpCmd, "%s/%s", tmpPath->element, command);
      if (access(tmpCmd, F_OK) == 0)
      {
        printf("%s\n", tmpCmd);
        char *tmp = tmpCmd;
        free(tmpCmd);
        return tmp;
      }
      else if (access(tmpCmd, F_OK) != 0 && tmpPath->next == NULL)
      {
        free(tmpCmd);
        break;
      }
      tmpPath = tmpPath->next;
    }
  }
  //free(tmpCmd);
  return NULL;
}

//---------------------------------------------------------------------------------------------------------------------------------

/* loop through pathlist until finding command and return it.  Return
   NULL when not found. */

void list(char *dir)
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
} /* list() */

/*
void exec(){

}

void prompt(){
  
}
*/

//If length isn't used, scrap it.
int getInput(char *strBuffer)
{
  int length = 0;
  if (fgets(strBuffer, BUFFERSIZE, stdin) != 0)
  {
    length = strlen(strBuffer);
    strBuffer[length - 1] = '\0';
  }
  return length;
}

//*argv array is used to store arguments for the command passed in, i.e. index 0 = command,
//index 1+ = args for that command
char **inputToArray(char *input, char **args, int *argsCount)
{
  int countForEndChar = 0;
  int countOfArgs = 0;
  char buff[BUFFERSIZE] = "";
  strcpy(buff, input);
  char *temp = strtok(buff, " ");

  //means there's more arguments, increment the amt of arguments

  while (temp)
  {
    //printf("%s\n",temp);
    countForEndChar++;
    temp = strtok(NULL, " ");
  }

  args = malloc((countForEndChar + 2) * sizeof(char *));
  args[countForEndChar + 1] = '\0';
  //argv[count+1] = NULL; //sets last index to the escape character to let exec know when to stop

  //  input = strtok(NULL, " ");
  strcpy(buff, input);

  temp = strtok(buff, " ");

  while (temp)
  {
    int len = strlen(temp);
    args[countOfArgs] = (char *)malloc((len + 1) * sizeof(char));
    strcpy(args[countOfArgs], temp);
    countOfArgs++;
    *argsCount = countOfArgs;
    temp = strtok(NULL, " ");
  }
  //char **tempArgs = args;
  //free (args);
  return args;
}
