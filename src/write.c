/* File for write function */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include "fs.h"

int myfs_write(char* input_file, char* destination_path, inode_t* inode_table, char* dbs, char* fs_name){
    struct stat src_file_stat;

    if (stat(input_file, &src_file_stat) == 0){
        int source_size =  (intmax_t) src_file_stat.st_size;
        char buf[source_size+1];
        if (S_ISDIR(src_file_stat.st_mode)){
            printf("Cannot write %s to %s, because source is not a file\n", input_file, destination_path);
            return 1;
        }

        int fd = open(input_file, O_RDONLY);
        ssize_t bytes_read = read(fd, buf, source_size+1);
        close(fd);

        load_inodes(fs_name, inode_table);

        int quotient = source_size / DATABLOCK_SIZE;
        int remainder = source_size % DATABLOCK_SIZE;
        int size_in_dbs = quotient + ((remainder == 0) ? 0 : 1);

        int free = get_free_db(dbs,size_in_dbs);
        int free_inode = get_free_inode(inode_table);
 
        if ((free_inode != -1) && (free != -1)){
            FILE* fp = fopen(fs_name, "wb");
            inode_t inode_fromfs = get_inode(input_file, inode_table);
            // if no inode with the same filename is not found then proceed
            if (inode_fromfs.inode_number == -1){ 
                inode_t inode = {
                    .inode_number = (free_inode+1),
                    .inode_type = 'f',
                    .db_size = DATABLOCK_SIZE,
                    .db_count = size_in_dbs,
                    .db_pt = free
                };

                printf("free inode: %d | %d %d %d \n", free_inode, inode.inode_number, inode.db_count, inode.db_pt);                
                strncpy(inode.filename, input_file, 32 * sizeof(char));

                fseek(fp, sizeof(superblock_t) + (free_inode * sizeof(inode_t)), SEEK_SET);
                ssize_t bytes_written = fwrite(&inode, sizeof(inode_t), 1, fp);

                fseek(fp, INODE_COUNT * sizeof(inode_t) + sizeof(superblock_t)+ free, SEEK_SET);
                bytes_written = fwrite(buf, sizeof(char), source_size+1, fp);
                fclose(fp);
            }
        }
    } else {
        fprintf(stderr, "Error: Could not open file %s (%s) \n", input_file, strerror(errno));
        printf("usage: ./myfs <fs> write <src-file> <destination-path> \n");
    }

    return 0;
}