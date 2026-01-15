#include <stdio.h>
#include <stdlib.h>

void printFD(FILE* fd){
    int c;
    while((c = getc(fd)) != EOF){
        putc(c, stdout);
    }
}

int main(int argc, const char** argv) {
  
    if(argc == 1){
        printFD(stdin);
        return 0;
    }
    else{
        for (int i = 0; i < argc-1; i++) {
            FILE* fd = fopen(argv[i+1], "r");
            if(fd == NULL){
                // printf("File doesn't exist: %s\n", argv[i+1]);
                fprintf(stderr, "File doesn't exist: %s\n", argv[i+1]);
                continue;
            }
            printFD(fd);
            fclose(fd);
        }
    }

    return 0;
}
