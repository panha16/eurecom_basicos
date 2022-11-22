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

        // int free = get_free_db(dbs);
        // int free_inode = get_free_inode(inode_table);
        int free = 0;
        int free_inode = 0;
     
        FILE* fp = fopen(fs_name, "wb");

        if ((free_inode != -1) && (free != -1)){

            inode_t inode = {
                .filename= "Salut",
                .inode_number = 106
            };
            fseek(fp, sizeof(superblock_t), SEEK_SET);
            ssize_t bytes_written = fwrite(&inode, sizeof(inode_t), 1, fp);

            fseek(fp, INODE_COUNT * sizeof(inode_t) + sizeof(superblock_t), SEEK_SET);
            bytes_written = fwrite(buf, sizeof(buf), 1, fp);
            printf("myfs_write: %lld elements written \n");
        }
        fclose(fp);
    } else {
        fprintf(stderr, "Error: Could not open file %s (%s) \n", input_file, strerror(errno));
        printf("usage: ./myfs <fs> write <src-file> <destination-path> \n");
    }

    return 0;
}