#include "fs.h"
#include <stdio.h>

int read(const char *path_to_file){
    FILE *fptr;
    char file_content[1000];
    fptr = fopen("path_to_file","r");
    if (!fptr || fptr == NULL) {
        printf("cannot open file");
        return -1;
    }
    while (fgets(file_content,sizeof(file_content),fptr) != NULL){
        printf("%s",file_content);
    }
    fclose(fptr);
    return 0;

}