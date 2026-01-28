#include <stdio.h>
#include <stdlib.h>

void usage(){
    printf("USAGE: <source> <destination>\n");
}

int main(int argc, const char** argv){
    
    if(argc <= 1){
        usage();
        exit(-1);
    }

    FILE* src = fopen(argv[1], "rb");
    FILE* dest = fopen(argv[2], "wb");
    if(src == NULL || dest == NULL){
        printf("Error opening files!\n");
        exit(-1);
    }

    char c;
    while((c = getc(src)) != EOF){
        putc(c, dest);
    }

    return 0;
}
