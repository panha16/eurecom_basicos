#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include "fs.h"

int remove_file(char* fs_name,char *file_or_directory_path, inode_t* inode_table, char* datablocks){


    //loading inodes and retrieving inode from file_or_directory_path
    load_inodes(fs_name, inode_table);

    inode_t r_inode = get_inode(file_or_directory_path, inode_table);
    int db_number = r_inode.db_pt;
    int db_count = r_inode.db_count;

    if (inode_table[r_inode.inode_number] == -1 ){
        printf("file is not assigned an inode\n")
        return -1;
    }
    //erasing file data in the filesystem
    FILE* fp = fopen(fs_name,"rb+");

    //setting datablocks linked to the file to null
    fseek(fp,sizeof(superblock_t) + INODE_COUNT*sizeof(inode_t) + db_number*DATABLOCK_SIZE,SEEK_SET);
    char buf [DATABLOCK_SIZE*db_count];
    for (int i = 0;i<=DATABLOCK_SIZE*db_count;i++) buf[i]='\0';
    fwrite(buf,sizeof(char),DATABLOCK_SIZE*db_count,fp);

    //erasing inode from filesystem
    fseek(fp,sizeof(superblock_t) + sizeof(inode_t)*r_inode.inode_number , SEEK_SET);
    char buf_inode[sizeof(inode_t)*r_inode.inode_number];
    for (int i = 0;i<=sizeof(inode_t)*r_inode.inode_number;i++) buf_inode[i]='\0';
    fwrite(buf_inode,sizeof(char),sizeof(inode_t)*r_inode.inode_number,fp);

    //emptying datablocks linked to the file
    for (int i = db_number ; i < db_number + (DATABLOCK_SIZE*r_inode.db_count) ; i++){
        if (datablocks[i]!='\0'){
            datablocks[i]='\0';
        }
    }

    fclose(fp);
    return 0;
}
