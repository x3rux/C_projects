#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEMP_FLAG "-t"
#define CURR_FLAG "-t"

void tempConverter(const char* arg2, const char* arg3);

int main(int argc, const char* argv[]){

    if(argc == 1){
	printf("Please provide flags for use!\n");
	exit(-1);
    }
    
    const char* flag = argv[1];

    if(strcmp(flag, TEMP_FLAG) == 0){
	if(argc<4){
	    printf("Not enough arguments!\n");
	    exit(-1);
	}
	tempConverter(argv[2], argv[3]);
    }

    else{
	printf("No valid flag provided!\n");
	exit(-1);
    }

    return 0;
}

void tempConverter(const char* arg2, const char* arg3){
    float temp = (float)atof(arg2);
    char unit = (char)arg3[0];
    unit = tolower(unit);

    if(unit == 'c'){
	printf("Given temperature: %0.2fC\n", temp);
	printf("In Farhenheit: %.02fF\n", ((temp*1.8)+32));
    }
    else if (unit == 'f'){
	printf("Given temperature: %0.2fF\n", temp);
	printf("In Celsius is: %.02fC\n", ((temp-32)/1.8));
    }
    else{
	printf("Wrong arguments!\n");
	exit(-1);
    }
}
