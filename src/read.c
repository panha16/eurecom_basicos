#include "fs.h"
#include <stdio.h>

int read_file(const char *path_to_file){
    
    //retrieving filename path_to_file
    char *slash_filename = strrchr(file_or_directory_path, '/');
    char filename[10000];
    for (int i = 1; i <strlen(slash_filename);i++){
        filename[i-1] = slash_filename[i];
    }    

    //get inode from filename
    inode_t read_inode = get_inode(filename,inode_table);
    int db_number = read_inode.db_pt;

    //reading the datablock linked to the file
    int i = db_number;
    while (datablock[i]!='\0'){
        printf("%c\n",datablock[i]);
        i++;
    }
    return 0;
}