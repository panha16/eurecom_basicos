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
#include <libgen.h>
#include "fs.h"

int myfs_write(superblock_t* superblock, char* input_file, char* destination_path, inode_t* inode_table, char* dbs, char* fs_name){
    struct stat src_file_stat; int quotient, remainder, size_in_dbs, free_db, free_inode;
    int DB_COUNT = superblock->db_count;

    int limit_size = superblock->size;
    char c;
    if (stat(input_file, &src_file_stat) == 0){ // if source file exists or is accessible
        int source_size =  (intmax_t) src_file_stat.st_size;
        if (source_size > limit_size) {
            fprintf(stderr, "Error: File %s is bigger than the file system (%s) \n", input_file, fs_name);
            exit(1);
        }    
        char* buf = malloc(source_size + 1);
        if (S_ISDIR(src_file_stat.st_mode)){
            printf("Cannot write %s to %s, because source is not a file\n Exiting...\n", input_file, destination_path);
            exit(1);
        }
        int fd = open(input_file, O_RDONLY);
        read(fd, buf, source_size+1);
        close(fd);
LABEL1:
        load_inodes(fs_name, inode_table);

        quotient = source_size / DATABLOCK_SIZE;
        remainder = source_size % DATABLOCK_SIZE;
        size_in_dbs = quotient + ((remainder == 0) ? 0 : 1);

        free_db = get_free_db(dbs,size_in_dbs,DB_COUNT);
        free_inode = get_free_inode(inode_table);

        if ((free_inode != -1) && (free_db != -1)){
            FILE* fp = fopen(fs_name, "rb+");
            // if no inode with the same filename is not found then proceed
            if (get_inode(destination_path, inode_table).inode_number == -1){ 
                inode_t inode = { // initialize inode with info about source file
                    .inode_number = free_inode,
                    .inode_type = 'f',
                    .timestamp_access = src_file_stat.st_atim,
                    .timestamp_modify = src_file_stat.st_mtim,
                    .timestamp_metadata = src_file_stat.st_ctim,
                    .db_size = DATABLOCK_SIZE,
                    .db_count = size_in_dbs,
                    .db_pt = free_db
                };
                strncpy(inode.filename, destination_path, 32 * sizeof(char));

                fseek(fp, sizeof(superblock_t) + (free_inode * sizeof(inode_t)), SEEK_SET);
                fwrite(&inode, sizeof(inode_t), 1, fp);

                fseek(fp, INODE_COUNT * sizeof(inode_t) + sizeof(superblock_t) + free_db, SEEK_SET);
                fwrite(buf, sizeof(char), source_size+1, fp);
                fclose(fp);
            } else {
                fprintf(stderr, "Error: File %s already exists on the file system. \n", destination_path); exit(1);
            }
        } else {
            if ((free_db == -1) || (free_inode == -1)){
                    printf("Warning: Not enough space available for %s \n", input_file);
DECISION1:
                    printf("Would you like to overwrite the file system? (y/n) \n");
                    scanf("%c", &c);
                    switch (c){
                        case 'y': printf("Ok, deletion... \n");
                            intmax_t minimum = time(NULL);
                            int to_delete, free_space;
                            for (int i = 0; i < DATABLOCK_SIZE * DB_COUNT; i++){
                                if (dbs[i] == '\0'){
                                    free_space++;
                                }
                            }
                            while (free_space < source_size){ // This part has not been thoroughly tested
                                for (int i = 2; i < INODE_COUNT; i++){ // We sort the files by timestamp
                                    if (((intmax_t) inode_table[i].timestamp_modify.tv_sec) < minimum){
                                    minimum = (intmax_t) inode_table[i].timestamp_modify.tv_sec;
                                    to_delete = i;
                                    }
                                }
                                printf("Deleted file %s \n", inode_table[to_delete].filename);
                                remove_file(fs_name,inode_table[to_delete].filename,inode_table,dbs);
                                free_space = free_space + (inode_table[to_delete].db_count * DATABLOCK_SIZE);
                            }
                            goto LABEL1;
                        case 'n': printf("Ok, aborting write instruction... \n"); exit(0);
                        default: goto DECISION1;
                    }
                
            }
        }
        free(buf);
    } else {
        fprintf(stderr, "Error: Could not open file %s (%s) \n", input_file, strerror(errno));
        printf("usage: ./myfs <fs> write <src-file> <destination-path> \n");
    }
    return 0;
}