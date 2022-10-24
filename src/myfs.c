// BasicOS project: Make a custom file system.
//
//  Filesystem main file.
//  Made by Ahmed Ghaleb, Guillaume Ung & William Chieu.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include "fs.h"


int main(int argc, char* argv[]){

    // int rflag = 0;
    // int dflag = 0;
    // int bflag = 0;
    // int kflag = 0;
    // int mflag = 0;
    // int gflag = 0;
    static int stat_flag;
    
    char *rvalue = NULL;
    char *dvalue = NULL;
    int index;
    char* fs_name = argv[1];

    if (argc < 4) {
        printf("usage: myfs <FS name> <cmd> <args> \n");
        exit(1);
    }

    char* commands[] = {"create", "write", "read","remove", "size", "ls"};



    if (strcmp(argv[2], commands[1]) == 0){
        printf("write command recognized \n");
    }

    else if (strcmp(argv[2], commands[4]) == 0){
        for (int i = 2; i < argc; i++){
            if (strcmp(argv[i], "-stat") == 0){
                stat_flag = 1;
                break;
            }
        }
        printf("size command recognized, stat flag state: %d \n", stat_flag);
    }
    exit (0);
    }