#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// BUILTIN COMMANDS
#define CD "cd"

char** tokenize(char* line){
    char** args = calloc(64, sizeof(char*));
    char* delims = " \n";
   
    int i = 0;
    char* token = strtok(line, delims);
    while(token != NULL){
        args[i++] = token;
        token = strtok(NULL, delims);
    }

    args[i] = NULL;
    return args;
}


int main(){

    char* line = NULL;
    size_t  size = 0;
    ssize_t nread;

    while(1) {
        printf("myshell>>");
        nread = getline(&line, &size, stdin);

        char** args = tokenize(line);

        if(strcmp(args[0],CD) == 0) {
            if(chdir(args[1]) != 0){
                fprintf(stderr, "ERROR: unable to change directory to %s\n", args[1]);
            }
            continue;
        }

        pid_t pid = fork();
        if (pid == 0){
            execvp(args[0], args);
            exit(1);
        }
        else{
            wait(NULL);
        }


        if (nread == EOF) break;
    }

    return 0;
}
