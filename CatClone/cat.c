#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char** argv) {
  
    int fileCount = argc-1;
    FILE** fd = (FILE**)malloc(argc * sizeof(FILE**));

    if(argc == 1){
        fd[0] = stdin;
        fileCount = 1;
    }
    else{
        for(int i = 0; i < fileCount; i++) {
            fd[i] = fopen(argv[i+1], "r");
        }
    }
  
    for (int i = 0;  i < fileCount;  i++) {
        char c;
        while((c = getc(fd[i])) != EOF){
            putc(c, stdout);
        }
    }

    return 0;
}
