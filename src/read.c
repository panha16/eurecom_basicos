#include "fs.h"
#include <stdio.h>

int read_file(const char *path_to_file){
    FILE *fptr;
    int c;
    fptr = fopen(*path_to_file,"r");
    if (!fptr || fptr == NULL) {
        printf("cannot open file");
        return -1;
    }
    while (1){
        c = fgetc(fptr);
        if (feof(fptr)) break;  //end of file reached
        printf("%c",c);
    }
    fclose(fptr);
    return 0;

}