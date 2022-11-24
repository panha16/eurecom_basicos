// BasicOS project: Make a custom file system.
//
//  Filesystem main file.
//  Made by Ahmed Ghaleb, Guillaume Ung & William Chieu.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include "fs.h"


int main(int argc, char* argv[]){

    int rflag;
    // int dflag;
    int bflag;
    int kflag;
    int mflag;
    int gflag;
    static int stat_flag;
    superblock_t superblock;
    
    // char *rvalue = NULL;
    // char *dvalue = NULL;
    char* src_file;
    char* dst_path;
    char* fs_name = argv[1];

    if (argc < 4) {
        printf("usage: myfs <FS name> <cmd> <args> \n");
        exit(1);
    }

    char* commands[] = {"create", "write", "read","remove", "size", "ls"};

    // for read & write commands we only have one source file
    // so it is reasonable to have only one stat struct
    struct stat src_file_stat;

    // --------------------------- SUPERBLOCK ------------------------ //
    inode_t inode_table[10000];
    char datablocks[DB_COUNT * DATABLOCK_SIZE];

    myfs_init(fs_name, 10);
    myfs_load(fs_name, superblock, inode_table, datablocks);

    superblock.inode_count = 10000;
    superblock.db_count = 1500;
    superblock.inode_table_pt = inode_table;

    // ------------------------ WRITE --------------------------- //

    if ((strcmp(argv[2], commands[1]) == 0) && (argc > 4)){
        printf("filesystem: %s, source file: %s, dest file: %s \n", fs_name, argv[3], argv[4]);
        char* src_file = argv[3];
        char* dst_path = argv[4];

        if (stat(src_file, &src_file_stat) == 0){

            myfs_write(src_file, dst_path, inode_table, datablocks, fs_name);
            
            load_inodes(fs_name, inode_table);
            myfs_load(fs_name, superblock, inode_table, datablocks);
            for (int i =0; i<20; i++) printf("%c \n", datablocks[i]);
            printf("%s \n", inode_table[0].filename);
            printf("%d \n", inode_table[0].inode_number);
            printf("%s \n", inode_table[1].filename);
            printf("%d \n", inode_table[1].inode_number);
            
        } else {
            fprintf(stderr, "Error: Could not open file %s (%s) \n", src_file, strerror(errno));
            printf("usage: ./myfs <fs> write <src-file> <destination-path> \n");
        }
    }

    // ------------------------ END OF WRITE --------------------------- //

    // ------------------------ SIZE --------------------------- //
    else if (strcmp(argv[2], commands[4]) == 0){
        printf("size command recognized, stat flag state: %d \n", stat_flag);
        char* src_file = argv[argc-1]; // according to the project description, path-to-dir comes last
        for (int i = 2; i < argc; i++){
            if (strcmp(argv[i], "-stat") == 0){
                stat_flag = 1;
            }
            if (strcmp(argv[i], "-r") == 0){
                rflag = 1;
            }
            if (strcmp(argv[i], "-b") == 0){
                bflag = 1;
            }
            if ((strcmp(argv[i], "-mb") == 0) || (strcmp(argv[i], "-MB") == 0) 
                || (strcmp(argv[i], "-m") == 0) || (strcmp(argv[i], "-M") == 0)){
                mflag = 1;
            }
            if ((strcmp(argv[i], "-kb") == 0) || (strcmp(argv[i], "-kb") == 0)
                || (strcmp(argv[i], "-k") == 0) || (strcmp(argv[i], "-K") == 0)){
                printf("size will be in Kbytes \n");
                kflag = 1;
            }
            if ((strcmp(argv[i], "-gb") == 0) || (strcmp(argv[i], "-GB") == 0)
                || (strcmp(argv[i], "-g") == 0) || (strcmp(argv[i], "-G") == 0)){
                gflag = 1;  
            }
        }
        if (stat(src_file, &src_file_stat) == 0){
            printf("File size:                %jd bytes\n", (intmax_t) src_file_stat.st_size);
            myfs_size(fs_name, src_file, rflag, '\0', 0, inode_table);

        } else {
            // File can't be located
            printf("Error!!! \n");
        }
    }
    // ------------------------ END OF SIZE --------------------------- //


    else if (strcmp(argv[2],commands[3])==0){     
        printf("remove command recognized \n");
        if (argv[4]!=0){        //user wants to remove a file
            remove_file(argv[4],inode_table, datablocks);
            printf("succesfully removed file %s\n", argv[4]);
        }   
        else {      //user wants to remove a directory
            // if (ls(argv[3],0,0) == 0){      //directory is empty
            //     remove(argv[3]);
            //     printf("succesfully removed directory %s\n", argv[3]);
            // }
            // else printf("cannot use remove, directory is not empty\n");

        }
    }

    else if (strcmp(argv[2],commands[2]) == 0){
        printf("read command recognized \n");
        if (!read_file(fs_name, argv[3], datablocks)) printf("file could not be read\n");
        printf("successfully read following file : %d \n",read_file(argv[3]));
        
    }
    exit (0);
    }