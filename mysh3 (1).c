#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int command(char **args, int pipes) {

    const int commands = pipes + 1;
    int i = 0;
    pipes=1;
    int pipefds[2*pipes];

    for(i = 0; i < pipes; i++){
        if(pipe(pipefds + i*2) < 0) {
            
            exit(EXIT_FAILURE);
        }
    }

    int pid;
    int status;

    int j = 0;
    int k = 0;
    int s = 1;
    int place;
    int commandStarts[10];
    commandStarts[0] = 0;

   

    while (args[k] != NULL){
        if(!strcmp(args[k], "|")){
            args[k] = NULL;
            
            commandStarts[s] = k+1;
            s++;
        }
        k++;
    }



    for (i = 0; i < commands; ++i) {
        
        place = commandStarts[i];

        pid = fork();
        if(pid == 0) {
            
            if(i < pipes){
                if(dup2(pipefds[j + 1], 1) < 0){
                    
                    exit(EXIT_FAILURE);
                }
            }

            
            if(j != 0 ){
                if(dup2(pipefds[j-2], 0) < 0){
                    
                    exit(EXIT_FAILURE);
                }
            }

            int q;
            for(q = 0; q < 2*pipes; q++){
                    close(pipefds[q]);
            }

                     
             if( execvp(args[place], args+place) < 0 ){
                    
                    exit(EXIT_FAILURE);
            }
        }
        else if(pid < 0){
            
            exit(EXIT_FAILURE);
        }

        j+=2;
    }

    for(i = 0; i < 2 * pipes; i++){
        close(pipefds[i]);
    }

    for(i = 0; i < pipes + 1; i++){
        wait(&status);
    }
}

















int launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
   
    if (execvp(args[0], args) == -1) {
      
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    
  } else {
    
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
  const char *i="|";
  const char *u="cd";
  char *line;
  char **args1;
  char **args;
  const char *y="exit";
  int pipes = 1;
  int b;
 
  do {
    printf("$ ");
    line = read_line();
    char* cmd = line;
    char* next = strchr(cmd,  '|');
    if (next == NULL) {
       args = split_line(line);
       launch(args); 
       if (strcmp(args[0],u) == 0) {
       
          if (chdir(args[1]) != 0) {
              
      
       } 
          }
     } else {
         args = split_line(line);
         
         command(args,pipes);
        }
    
    b=strcmp(line,y);
    
       
    


    if (strcmp(args[0],u) == 0) {
       
   if (chdir(args[1]) != 0) {
     
    
    }
   }

    
  } while (b!=0);
}


int main(int argc, char **argv)
{
  

 
  loop();

 

  return EXIT_SUCCESS;
}

