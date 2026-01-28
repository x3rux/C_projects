#include <stdio.h>
#include <stdlib.h>

void usage(){
    fprintf(stderr, "USAGE: <source> <destination>\n");
}

int main(int argc, const char** argv){
    
    if(argc < 3){
        usage();
        exit(-1);
    }

    FILE* src = fopen(argv[1], "rb");
    FILE* dest = fopen(argv[2], "wb");
    if(src == NULL || dest == NULL){
      fprintf(stderr,"Error reading files!\n");
        exit(-1);
    }

    int c;
    while((c = getc(src)) != EOF){
        putc(c, dest);
    }
    
    fclose(src);
    fclose(dest);
    return 0;
}
