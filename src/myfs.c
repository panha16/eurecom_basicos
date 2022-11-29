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
#include <sys/time.h>

#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include "fs.h"


int main(int argc, char* argv[]){

    int rflag = 0, kflag = 0, mflag = 0, gflag = 0;
    static int stat_flag = 0;
    superblock_t superblock;
    
    // char *rvalue = NULL;
    // char *dvalue = NULL;
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

    // J'utilise ça pour effectuer mes tests en attendant `create` — Ahmed
    struct stat fs_file_stat;
    if (stat(fs_name, &fs_file_stat) != 0){
        myfs_init(fs_name, 10);
    }

    myfs_load(fs_name, superblock, inode_table, datablocks);

    superblock.inode_count = 10000;
    superblock.db_count = 1500;
    superblock.inode_table_pt = inode_table;

    // ------------------------ WRITE --------------------------- //

    if ((strcmp(argv[2], commands[1]) == 0) && (argc > 4)){
        char* src_file = argv[3];
        char* dst_path = argv[4];

        if (stat(src_file, &src_file_stat) == 0){

            // for (int i =0; i<20; i++) printf("%c \n", datablocks[i]);
            // printf("file name %s \n", inode_table[2].filename);
            // printf("inode number %d \n", inode_table[2].inode_number);
            // printf("size in db %d \n", inode_table[2].db_count);
            // printf("dbptr %d \n", inode_table[2].db_pt);

            // printf("file name %s \n", inode_table[0].filename);
            // printf("inode number %d \n", inode_table[0].inode_number);
            // printf("size in db %d \n", inode_table[0].db_count);
            // printf("dbptr %d \n", inode_table[0].db_pt);
            
            // printf("file name %s \n", inode_table[1].filename);
            // printf("inode number %d \n", inode_table[1].inode_number);
            // printf("size in db %d \n", inode_table[1].db_count);
            // printf("dbptr %d \n", inode_table[1].db_pt);

            if (myfs_write(src_file, dst_path, inode_table, datablocks, fs_name) != 0) return 1;
            
            // myfs_load(fs_name, superblock, inode_table, datablocks);
            load_inodes(fs_name, inode_table);
            // for (int i =0; i<20; i++) printf("%c \n", datablocks[i]);
            printf("file name %s \n", inode_table[2].filename);
            printf("inode number %d \n", inode_table[2].inode_number);
            printf("size in db %d \n", inode_table[2].db_count);
            printf("dbptr %d \n", inode_table[2].db_pt);

            printf("file name %s \n", inode_table[0].filename);
            printf("inode number %d \n", inode_table[0].inode_number);
            printf("size in db %d \n", inode_table[0].db_count);
            printf("dbptr %d \n", inode_table[0].db_pt);
            
            printf("file name %s \n", inode_table[1].filename);
            printf("inode number %d \n", inode_table[1].inode_number);
            printf("size in db %d \n", inode_table[1].db_count);
            printf("dbptr %d \n", inode_table[1].db_pt);

            printf("file name %s \n", inode_table[3].filename);
            printf("inode number %d \n", inode_table[3].inode_number);
            printf("size in db %d \n", inode_table[3].db_count);
            printf("dbptr %d \n", inode_table[3].db_pt);

            printf("file name %s \n", inode_table[4].filename);
            printf("inode number %d \n", inode_table[4].inode_number);
            printf("size in db %d \n", inode_table[4].db_count);
            printf("dbptr %d \n", inode_table[4].db_pt);
            

            // for (int i =0; i<20; i++) printf("%c \n", datablocks[i]);


            // William, tu peux utiliser ça pour print les time des fichiers
            // struct tm *tmbuf;
            // char str[64];

            // tmbuf = gmtime(&inode_table[2].timestamp_access);
            // if (tmbuf == NULL)
            //     err(1, "gmtime");
            // if (strftime(str, sizeof(str), "%a %b %e %T %Y %Z", tmbuf) == 0)
            //     err(1, "strftime");
            // printf("%s \n", str);

        } else {
            fprintf(stderr, "Error: Could not open file %s (%s) \n", src_file, strerror(errno));
            printf("usage: ./myfs <fs> write <src-file> <destination-path> \n");
        }
    }

    // ------------------------ END OF WRITE --------------------------- //

    // ------------------------ SIZE --------------------------- //
    else if (strcmp(argv[2], commands[4]) == 0){
        char* src_file = argv[argc-1]; // according to the project description, path-to-dir comes last
        for (int i = 2; i < argc; i++){
            if (strcmp(argv[i], "-stat") == 0){
                stat_flag = 1;
            }
            if (strcmp(argv[i], "-r") == 0){
                rflag = 1;
            }
            if ((strcmp(argv[i], "-mb") == 0) || (strcmp(argv[i], "-MB") == 0) 
                || (strcmp(argv[i], "-m") == 0) || (strcmp(argv[i], "-M") == 0)){
                mflag = 1;
            }
            if ((strcmp(argv[i], "-kb") == 0) || (strcmp(argv[i], "-kb") == 0)
                || (strcmp(argv[i], "-k") == 0) || (strcmp(argv[i], "-K") == 0)){
                kflag = 1;
            }
            if ((strcmp(argv[i], "-gb") == 0) || (strcmp(argv[i], "-GB") == 0)
                || (strcmp(argv[i], "-g") == 0) || (strcmp(argv[i], "-G") == 0)){
                gflag = 1;  
            }
        }
        
        if (mflag) myfs_size(fs_name, src_file, rflag, 'M', stat_flag, inode_table, datablocks);
        else if (kflag) myfs_size(fs_name, src_file, rflag, 'K', stat_flag, inode_table, datablocks);
        else if (gflag) myfs_size(fs_name, src_file, rflag, 'G', stat_flag, inode_table, datablocks);
        else myfs_size(fs_name, src_file, rflag, 'B', stat_flag, inode_table, datablocks);

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
        read_file(fs_name,argv[3],datablocks,inode_table);
    }
    exit (0);
    }