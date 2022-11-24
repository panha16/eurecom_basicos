#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABLOCK_SIZE 4096
#define SUPERBLOCK_SIZE 32

struct superblock {
    int db_count;
    int inode_count;
    char* inode_table_pt;
    char* free_inode_pt;
    char* free_db_pt;
};

struct inode {
    int inode_number;
    int inode_size;
    char name[8];
    char inode_type;
    char inode_rights;
    struct timespec timestamp_access;
    struct timespec timestamp_modify;
    struct timespec timestamp_metadata;
    int db_size;
    int db_count;
    char* db_pt; 
};

struct data_block{
    int next_block_num;
    char data[512];
};

struct superblock sb;
struct inode *inodes;
struct data_block *dbs;


int create(int size, char* fs_name){
    sb.inode_count = 10;
    sb.db_count = 100;

    // init inodes
    int i;
    inodes = malloc(sizeof(struct inode) * sb.inode_count);
    for (i=0; i< sb.inode_count; i++){
        inodes[i].inode_size = -1;
        strcpy(inodes[i].name, "emptyfi");
    }

    // init dbs
    dbs = malloc(sizeof(struct data_block) * sb.db_count);
    for (i=0; i< sb.db_count; i++){
        dbs[i].next_block_num = -1;
    }
    
    FILE* file;
    file = fopen(fs_name,"w+");

    // superblock
    fwrite(&sb, sizeof(struct superblock), 1, file);

    //inodes
    for (i=0; i< sb.inode_count; i++){
        fwrite (&(inodes[i]), sizeof(struct inode), 1, file);
    }

    //data_blocks
    for (i=0; i<sb.db_count; i++){
        fwrite (&(dbs[i]), sizeof(struct data_block), 1, file);
    }

    fclose(file);
    return 0;
}


int main(){
    create(10, "myfs");
    return 0;
}