#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "fs.h"

int read_file(char* fs_name,char *path_to_file, char* dbs, inode_t* table){

    load_inodes(fs_name, table);
    //get inode from filename
    inode_t read_inode = get_inode(path_to_file,table);
    int db_number = read_inode.db_pt;
    printf("datablock number is %d,inode number is %d,db count is %d\n",db_number,read_inode.inode_number,read_inode.db_count);
    for (int i = db_number ; i < db_number + (DATABLOCK_SIZE*read_inode.db_count) ; i++){
        if (dbs[i]=='\0') break;
        printf("%c\n",dbs[i]);
    }
    return 0;
}