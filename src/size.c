/* File for size function */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include "fs.h"


int size(char* path_to_directory, int recursive, char multiple, int stat){
    inode_t inode = get_inode(path_to_directory);
    if (inode.inode_type == 'd'){
        printf("Ok, function is good \n");
    } else {
        fprintf(stderr, "Invalid path. Path must point to directory \n");
        printf("usage: ./myfs <fs> <opt -b/-k/-m/-g> <opt -r> <path-to-directory> \n");
        return 1;
    }
}