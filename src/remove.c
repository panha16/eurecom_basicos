#include "fs.h"

void remove(const char *file_or_directory_path){
    free(*file_or_directory_path);
}