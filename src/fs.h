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
    char filename[32];
    int inode_number;
    char inode_type;
    char inode_rights;
    struct timespec timestamp_access;
    struct timespec timestamp_modify;
    struct timespec timestamp_metadata;
    int db_size;
    int db_count;
    char* db_pt;    // datablock pointer
} inode_t;

char read(const char *file_path);
void remove1(const char *file_or_directory_path);
int ls(const char *dir,int op_a,int op_l);