// BasicOS project: Make a custom file system.
//
//  Filesystem main file.
//  Made by Ahmed Ghaleb, Guillaume Ung & William Chieu.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "fs.h"

int main(int argc, char* argv[]){

    int rflag = 0;
    int dflag = 0;
    int bflag = 0;
    int kflag = 0;
    int mflag = 0;
    int gflag = 0;
    
    char *rvalue = NULL;
    char *dvalue = NULL;
    int index;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "dr:")) != -1)
        switch (c){
        case 'd':
            dflag = 1;
            dvalue = optarg;
            break;
        case 'r':
            rflag = 1;
            rvalue = optarg;
            break;
        case '?':
            if (optopt == 'r')
            fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
            fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
            fprintf (stderr,
                    "Unknown option character `\\x%x'.\n",
                    optopt);
            return 1;
        default:
            abort ();
        }

    printf ("rflag = %d, dflag = %d, rvalue = %s, dvalue = %s\n",
            rflag, dflag, rvalue, dvalue);

    for (index = optind; index < argc; index++){
        printf ("Non-option argument %s at index %d \n", argv[index], index);
        
    } 
    superblock_t super;
    super.db_count = 2000;
    super.inode_count = 100;
    printf("%d \n", sizeof(super));
    return 0;
}

