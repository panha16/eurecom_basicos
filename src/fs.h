/*!  fs.h
    File used for macros and structure definitions.
*/

#define DATABLOCK_SIZE 512 /*! */
#define SUPERBLOCK_SIZE 32
#define INODE_COUNT 10000 /*! Number of inodes in the FS */
#include <sys/time.h>
#include <time.h>

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
    int db_pt;   // datablock pointer
} inode_t;

typedef struct{
    int size;
    int db_count;
    int inode_count;
    inode_t* inode_table_pt;
    int free_inode_pt;
    int free_db_pt;
} superblock_t;


void ls(const char* dir);
inode_t get_inode(char* file_or_directory_path, inode_t* inode_table);
int get_free_inode(inode_t* inode_table);
bool is_inode_free(int inode_nb, int* inode_table);
int myfs_size(char* fs_name, char* path_to_directory, int recursive, char multiple, int stat, inode_t* table, char* dbs,int DB_COUNT);
int myfs_write(superblock_t* superblock, char* input_file, char* destination_path, inode_t* inode_table, char* dbs, char* fs_name);
int get_free_db(char* datablocks, int size_in_dbs,int nb_db);
int load_inodes(char* fsname, inode_t* inode_table);
int remove_file(char* fs_name,char *file_or_directory_path, inode_t* inode_table, char* datablocks);
int read_file(char* fs_name,char *path_to_file, char* dbs, inode_t* table);
int myfs_load(char* fsname, superblock_t superblock, inode_t* inode_table, char* datablocks);
int myfs_init(char* fs_name, int size);



