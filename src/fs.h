/*!  fs.h
    File used for macros and structure definitions.
*/

#define DATABLOCK_SIZE 4096 /*! */
#define SUPERBLOCK_SIZE 32
#define INODE_COUNT 10000 /*! Number of inodes in the FS */

typedef struct{
    char filename[32];
    int inode_number;
    char inode_type; // Directory, file
    char inode_rights;
    struct timespec timestamp_access;
    struct timespec timestamp_modify;
    struct timespec timestamp_metadata;
    int db_size;
    int db_count;
    int db_pt;    // datablock pointer
} inode_t;


typedef struct{
    int db_count;
    int inode_count;
    inode_t* inode_table_pt;
    char* free_inode_pt;
    char* free_db_pt;
} superblock_t;


char read(const char *file_path);
int remove_file(const char *file_or_directory_path);
int ls(const char *dir,int op_a,int op_l);
inode_t get_inode(char* file_or_directory_path, superblock_t superblock);
int get_free_inode(int* inode_table);
bool is_inode_free(int inode_nb, int* inode_table);
