#include <stdio.h>
#include <string.h>
#include <errno.h>

void printFD(FILE* fd){
    int c;
    while((c = getc(fd)) != EOF){
        putc(c, stdout);
    }
}

int cat(int argc, const char* argv[]){
    int err = 0;
    if(argc == 1){
        printFD(stdin);
        return 0;
    }
    else{
        for (int i = 1; i < argc; i++) {
            if(strcmp(argv[i], "-") == 0){
                printFD(stdin); 
                continue;
            }

            FILE* fd = fopen(argv[i], "rb");
            if(fd == NULL){
                err = 1;
                fprintf(stderr, "%s: %s\n", argv[i], strerror(errno));
                continue;
            }
            printFD(fd);
            fclose(fd);
        }
    }

    if(err == 1){
        return 1;
    }
    return 0;
}

int main(int argc, const char* argv[]) {
    return cat(argc, argv);  
}
