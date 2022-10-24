#define DATABLOCK_SIZE 4096

typedef struct{
    int db_count = 15;
    int inode_count = 10;
    char inode_table_pt;
    char free_inode_pt;
    char free_db_pt;
}superblock;

typedef struct{
    int inode_number;
    char inode_type;
    char inode_rights;
    
}inode;
