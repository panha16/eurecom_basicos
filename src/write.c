/* File for write function */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include "fs.h"

int myfs_write(char* input_file, char* destination_path, inode_t* inode_table, char* dbs, char* fs_name){
    struct stat src_file_stat; int quotient; int remainder; int size_in_dbs;
    int free; int free_inode;

    if (stat(input_file, &src_file_stat) == 0){
        int source_size =  (intmax_t) src_file_stat.st_size;
        char buf[source_size+1];
        if (S_ISDIR(src_file_stat.st_mode)){
            printf("Cannot write %s to %s, because source is not a file\n Exiting...\n", input_file, destination_path);
            return 1;
        }
        int fd = open(input_file, O_RDONLY);
        ssize_t bytes_read = read(fd, buf, source_size+1);
        close(fd);
LABEL1:
        load_inodes(fs_name, inode_table);
        quotient = source_size / DATABLOCK_SIZE;
        remainder = source_size % DATABLOCK_SIZE;
        size_in_dbs = quotient + ((remainder == 0) ? 0 : 1);

        free = get_free_db(dbs,size_in_dbs);
        free_inode = get_free_inode(inode_table);
 
        if ((free_inode != -1) && (free != -1)){
            FILE* fp = fopen(fs_name, "wb");
            inode_t inode_fromfs = get_inode(input_file, inode_table);
            // if no inode with the same filename is not found then proceed
            if (inode_fromfs.inode_number == -1){ 
                inode_t inode = {
                    .inode_number = (free_inode+1),
                    .inode_type = 'f',
                    .timestamp_access = src_file_stat.st_atim,
                    .timestamp_modify = src_file_stat.st_mtim,
                    .timestamp_metadata = src_file_stat.st_ctim,
                    .db_size = DATABLOCK_SIZE,
                    .db_count = size_in_dbs,
                    .db_pt = free
                };
                strncpy(inode.filename, input_file, 32 * sizeof(char));

                fseek(fp, sizeof(superblock_t) + (free_inode * sizeof(inode_t)), SEEK_SET);
                ssize_t bytes_written = fwrite(&inode, sizeof(inode_t), 1, fp);

                fseek(fp, INODE_COUNT * sizeof(inode_t) + sizeof(superblock_t)+ free, SEEK_SET);
                bytes_written = fwrite(buf, sizeof(char), source_size+1, fp);
                fclose(fp);
            } else {
                fprintf(stderr, "Error: File %s already exists on the file system. \n", input_file); return 1;
            }
        } else {
            if (free == -1){
                if (source_size > 10){
                    fprintf(stderr, "Error: File %s is bigger than the file system (%s) \n", input_file, fs_name);
                    exit(1);
                } else {
                    printf("Warning: Not enough datablocks available for %s \n", input_file);
                    printf("Would you like to overwrite the file system? (y/n) \n");
                    char c = fgetc(0);
                    DECISION1:switch (c){
                        case 'y': printf("Ok, deletion"); break;
                        case 'n': printf("Ok, aborting write instruction..."); exit(0);
                        default: goto DECISION1;
                    }
                }
            } else if (free_inode == -1) {
                printf("Warning: No available inode for %s \n", input_file);
                printf("Would you like to overwrite the file system? (y/n) \n");
                char c = fgetc(0);
                DECISION2:switch (c) {
                    case 'y': printf("Ok, deleting an inode...");goto LABEL1;break;
                    case 'n': printf("Ok, aborting write instruction..."); exit(0);
                    default: goto DECISION2;
                } 
            }
        }
    } else {
        fprintf(stderr, "Error: Could not open file %s (%s) \n", input_file, strerror(errno));
        printf("usage: ./myfs <fs> write <src-file> <destination-path> \n");
    }
    return 0;
}