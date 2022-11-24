# BasicOS Filesystem Project report
## Ahmed Ghaleb,William Chieu,Guillaume Ung

### Objective

The goal of this project is to create a simple filesystem in C and the to implement the following functions to this filesystem : "create","write","read","remove","ls","size".
The filesystem should support at least 10Mbytes and the size of a file should be at 5MBytes maximum.
To implement this filesystem, we had to define its structure by organizing the superblock,the inodes and the datablocks to then define their behaviour in regards to the functions.


### Filesystem structure

The filesystem is divided into 4 parts : the superblock, the inodes, the datablock and the files. We decided that our filesystem should contain 1500 data blocks and 10000 inodes. Given that a datablock weighs 4096 bytes and an inode 72 bytes, all the datablocks and the inodes amount 6.144Mbytes and 0.72Mbytes respectively. The superblock size is not mentioned here as it is very small compared to the rest.

#### Inodes


### Functions


### Subfunctions