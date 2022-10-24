#define DATABLOCK_SIZE 4096
#define SUPERBLOCK_SIZE 32

typedef struct{
    int db_count;
    int inode_count;
    char* inode_table_pt;
    char* free_inode_pt;
    char* free_db_pt;
} superblock_t;

typedef struct{
    int inode_number;
    char inode_type;
    char inode_rights;
    char timestamp_access;
    char timestamp_modify;
    char timestamp_metadata;
    int db_size;
    int db_count;
    char* db_pt;    // datablock pointer
} inode_t;

