#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>







int launch(char **args)
{
  pid_t pid, wpid;
  int status;
  const char *u="cd";
  int c;
  
  pid = fork();
  if (pid == 0) {
    
    if (execvp(args[0], args) == -1) {
      
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    
    
  } else {
    
   
  
    if (strcmp(args[0],u) == 0) {
       
   if (chdir(args[1]) != 0) {
      
    }


    }
  
   

   do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  
  return 1;
}



char *read_line(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; 
  getline(&line, &bufsize, stdin);
  return line;
}



#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}


void loop(void)
{
  char *line;
  char **args;
  const char *y="exit";
  
  int b;
  
  do {
    printf("$ ");
    line = read_line();
    args = split_line(line);
    b=strcmp(line,y);
    launch(args);
     
    

    
  } while (b!=0);
}


int main(int argc, char **argv)
{
  

 
  loop();

 

  return EXIT_SUCCESS;
}
