#include "fs.h"
#include <string.h>

int remove_file(const char *file_or_directory_path){
    //retrieving inode_t from file_or_directory_path    
    inode_t r_inode = get_inode(file_or_directory_path,superblock);
    inode_t null_inode;
    //empyting datablocks
    r_inode.db_count = 0;
    r_inode.db_size = 0;

    //updating tables linked to inode
    inode_table[r_inode.inode_number] = null_inode;
    free_inode_table[r_inode.inode_number] = 0;
    free_db_table[r_inode.db_pt] = 0;

    //retrieving filename from file_or_directory_path to delete the file
    char *slash_filename = strrchr(file_or_directory_path, '/');
    char filename[10000];
    for (int i = 1; i <strlen(slash_filename);i++){
        filename[i-1] = slash_filename[i];
    }
    return remove(filename);

}
