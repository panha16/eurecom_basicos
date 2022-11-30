#define _GNU_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

void ls(const char* dir){ // Not working for the FileSystem but works for Windows
    DIR *rep;
    rep = opendir(dir);
    struct dirent *lecture;
    struct stat statbuf;
    lecture = readdir(rep);
    int loop = 0;

    while (lecture != NULL)
        {
        printf("%s\n", lecture->d_name);
        if (loop >= 2){
            stat(lecture->d_name, &statbuf);
            if(S_ISREG(statbuf.st_mode) == 0){ 
                chdir(lecture->d_name);
                char* current_dir = get_current_dir_name();
                ls(current_dir);
                chdir("..");
                printf("-----------------------\n");
                }
            }
        lecture = readdir(rep);
        loop = loop + 1;
        
        }
    closedir(rep);
}

