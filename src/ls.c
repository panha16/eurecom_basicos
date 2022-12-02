#define _GNU_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>


void ls(const char* dir){ 
    DIR *rep;
    rep = opendir(dir);
    struct dirent *lecture;
    struct stat statbuf;
    lecture = readdir(rep);
    int loop = 0;

    while (lecture != NULL)  // While there is still a file to read, the program loops
        {
        printf("%s\n", lecture->d_name);
        if (loop >= 2){     // So that the program doesn't go to the current directory, nor the parent directory
            stat(lecture->d_name, &statbuf);
            if(S_ISREG(statbuf.st_mode) == 0){ // If the file is a directory 
                chdir(lecture->d_name); // Change to the new directory
                char* current_dir = get_current_dir_name();
                ls(current_dir); // Recurse
                chdir("..");
                printf("-----------------------\n");
                }
            }
        lecture = readdir(rep);
        loop = loop + 1;
        
        }
    closedir(rep);
}

