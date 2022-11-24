/*!  fs.h
    File used for macros and structure definitions.
*/

#define DATABLOCK_SIZE 4096 /*! */
#define SUPERBLOCK_SIZE 32
#define INODE_COUNT 10000 /*! Number of inodes in the FS */
#define DB_COUNT 1500
#define CHARCNT 6144000

typedef struct{
    char filename[32];
    int inode_number;
    char inode_type; // Directory, file
    char inode_rights;

    int db_size;
    int db_count;
    int db_pt;   // datablock pointer
} inode_t;
typedef struct{
    int db_count;
    int inode_count;
    inode_t* inode_table_pt;
    int free_inode_pt;
    int free_db_pt;
} superblock_t;


// char read(const char *file_path);
void remove1(const char *file_or_directory_path);
int ls(const char *dir,int op_a,int op_l);
inode_t get_inode(char* file_or_directory_path, inode_t* inode_table);
int get_free_inode(inode_t* inode_table);
bool is_inode_free(int inode_nb, int* inode_table);
int myfs_size(char* fs_name, char* path_to_directory, int recursive, char multiple, int stat, inode_t* table);
int myfs_write(char* input_file, char* destination_path, inode_t* inode_table, char* dbs, char* fs_name);
int get_free_db(char* datablocks);
int load_inodes(char* fsname, inode_t* inode_table);
