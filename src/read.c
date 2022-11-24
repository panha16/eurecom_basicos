#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "fs.h"

int read_file(char* fs_name, const char *path_to_file, char* dbs){

    inode_t* inode_table;
    load_inodes(fs_name, inode_table);
    
    //retrieving filename path_to_file
    char *slash_filename = strrchr(path_to_file, '/');
    char filename[10000];
    for (int i = 1; i <strlen(slash_filename);i++){
        filename[i-1] = slash_filename[i];
    }    

    //get inode from filename
    inode_t read_inode = get_inode(filename,inode_table);
    int db_number = read_inode.db_pt;

    //reading the datablock linked to the file
    int i = db_number;
    while (dbs[i]!='\0'){
        printf("%c\n",dbs[i]);
        i++;
    }
    return 0;
}