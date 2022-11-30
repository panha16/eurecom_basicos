# BasicOS Filesystem Project report
## Ahmed Ghaleb,William Chieu,Guillaume Ung





Objective
===============

The goal of this project is to create a simple filesystem in C and to implement the following functions to this filesystem : "create", "write" ,"read" ,"remove", "ls", "size".
The filesystem should support at least 10Mbytes and the size of a file should be at most 5Mbytes.
To implement this filesystem, we had to define its structure by organizing the superblock,the inodes and the datablocks to then define their behaviour in regards to the functions.


Filesystem structure
===============

The filesystem is a file divided into 4 parts : the superblock, the inodes, the datablock and the files. We decided that our filesystem should contain **1500 data blocks** and **10000 inodes**. Given that a datablock weighs 4096 bytes and an inode 72 bytes, all the datablocks and the inodes amount to 6.144Mbytes and 0.72Mbytes respectively. The superblock size is not mentioned here as it is very small compared to the rest.


### Superblock
The superblock is composed of the number of datablocks and inodes, and pointers to 3 tables : one to all inodes, one to free inodes and one to free datablocks.


### Inodes
To each file is dedicated one and only one inode. This inode is composed of the file name, the inode number, the file type,the permissions given, the timestamp and informations concerning the datablocks linked to this inode such as their size, their amount and the pointer to these datablocks.


### Datablocks
A datablock is represented by a list of 4096 single characters ('\0' being an empty character).


### Files
In this project, all handled files will be .txt files (with a maximum size of 5Mbytes).


Functions
===============

### create
```
int create(int size, char* fs_name)
```
The create function initializes the filesystem and takes as argument the size and name of the filesystem. By using this function, all inodes and datablocks are initialized.

### ls
```
int ls(char opt_r,char opt_d,char path_to_directory)
```
The ls function prints the name of all files located in the the path specified by the function argument. 
If the user specifies -r as a function argument, ls will print the name of all files in the path directory and in the sub-directories.
If the user specifies -d as a function argument, ls will print the names of all files in the path directory sorted by date.

### read
```
int read_file(char* fs_name,char *path_to_file, char* dbs, inode_t* table)
```
The read function prints all the text in the file specified by path_to_file. 
To do so, it seeks the inode of the file to find the datablocks. Printing the characters located in these datablocks will give us the text of the file. 

### remove
```
int remove_file(char* fs_name,char *file_or_directory_path, inode_t* inode_table, char* datablocks)
```
The remove function removes the file or the directory specified by the argument. If it is a directory, it is only removed if it is empty. 
To remove a file, the function erases the datablock data and inode data from the filesystem. Then, it empties the datablocks by setting each character to the null character '\0'.

### write
```
int write(char input_file, char destination_path)
```
The write function jsp frr 

### size 
```
int size (char opt_r,char opt,char opt_stat,char path_to_directory)
```
The size function prints the total size of the directory specified by the path_to_directory argument.
If the users specifies -r, *size* will print the total size of the directory and also the size of all sub-directories.
If the user specifies -b,-k,-m or -g, the size will be provied in bytes, kilobytes, megabytes, or gigabytes respectively.
If the user specfies -stat, *size* will also print the size of the partition table (superblock + inodes) and the files in regards to the total size of the filesystem.


Subfunctions
================

To facilitate the implementation of the forementioned functions and of the filesystem in general, we thought useful to create subfunctions.

### get_inode
```
inode_t get_inode(char* filename, inode_t* inode_table)
```
This function finds the inode from the filename and returns it.

### get_free_db
```
int get_free_db(char* datablocks, int size_in_dbs)
```
This function returns the index of the first free datablock among all datablocks.

### get_free_inode
```
int get_free_inode(inode_t* inode_table)
```
This function returns the index of the first free inode among all inodes.

### myfs_load
```
int myfs_load(char* fsname, superblock_t superblock, inode_t* inode_table, char* datablocks)
```
This function loads the filesystem previously initialized. It loads the inode table and all datablocks to be ready for use.

### load_inodes
```
int load_inodes(char* fsname, inode_t* inode_table)
```
This function loads inode from the saved filesystem.

### myfs_init
```
int myfs_init(char* fs_name, int size)
```
Budget version of create















### myfs_init
```
int myfs_init(char* fs_name, int size)
```
This function initializes the filesystem **fs_name** to the size **size** (in Mbytes).

### myfs_load
```
int myfs_load(char* fsname, superblock_t superblock, inode_t* inode_table, char* datablocks)
```
This function loads the filesystem previously initialized. It loads the inode table and all datablocks to be ready for use.

### load_inodes
```
int load_inodes(char* fsname, inode_t* inode_table)
```
This function loads the inode from the fielsystem to the table of inode inode_table.s
### get_inode
```
inode_t get_inode(char* filename, inode_t* inode_table)
```
This function finds the inode from the filename and returns it.

### get_free_db
```
int get_free_db(char* datablocks)
```
This function returns the index of the first free datablock among all datablocks.

### is_inode_free
```
bool is_inode_free(int inode_nb, int* inode_table)
```
This functions checks if an inode is free or not.

### get_free_inode
```
int get_free_inode(int* inode_table)
```
This function returns the index of the first free inode among all inodes.

### inode_to_str
```
void inode_to_str(inode_t* inode)
```

### update_inode
```
int update_inode(int inode_number, inode_t inode, int* free_inode_table, inode_t* inode_table)
```




