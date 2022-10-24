#define DATABLOCK_SIZE 4096


typedef struct{
    int db_count = 2000;
    int inode_count = 100;
    char* inode_table_pt;
    char* free_inode_pt;
    char* free_db_pt;
}superblock;

typedef struct{
    int inode_number;
    char inode_type;
    char inode_rights;
    char timestamp_access;
    char timestamp_modify;
    char timestamp_metadata;
    int db_size;
    int db_count;
    int * db_pt;    //datablock pointer
}inode;
