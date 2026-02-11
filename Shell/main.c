#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        for (int i = 0;; i++) {
            printf("%s", args[i]);
            if (args[i] == NULL){
                free(args);
                break;
            }
        }
        

        if (nread == EOF) break;
    }

    return 0;
}
