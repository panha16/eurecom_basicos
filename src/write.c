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
        char* buf[source_size+1];
        if (S_ISDIR(src_file_stat.st_mode)){
            printf("Cannot write %s to %s, because source is not a file\n", input_file, destination_path);
            return 1;
        }
        int fd = open(input_file, O_RDONLY);
        ssize_t bytes_read = read(fd, buf, source_size+1);

        int free = get_free_db(dbs);
        int free_inode = get_free_inode(inode_table);
        inode_t* object = malloc(sizeof(inode_t));
        strcpy(object->filename, input_file);
        object->inode_number=100;
        printf("%d free inode \n", free_inode);

        int fd_fs = open(fs_name, O_WRONLY);

        if ((free_inode != -1) && (free != -1)){
            int fd_fs = open(fs_name, O_WRONLY);
            lseek(fd_fs, sizeof(superblock_t), SEEK_SET);
            ssize_t bytes_written = write(fd_fs, object,sizeof(inode_t));
            printf("inode written at %d \n", free_inode+24);

            int nb_db = source_size % DATABLOCK_SIZE;
            lseek(fd_fs, free+ DB_COUNT * sizeof(inode_t) + sizeof(superblock_t) + DB_COUNT * DATABLOCK_SIZE, SEEK_SET);
            bytes_written = write(fd_fs, buf, source_size+1);
            printf("%ld bytes written to %s at %d\n", bytes_written, fs_name, free);
            close(fd);
        }
    } else {
        fprintf(stderr, "Error: Could not open file %s (%s) \n", input_file, strerror(errno));
        printf("usage: ./myfs <fs> write <src-file> <destination-path> \n");
    }

    return 0;
}