# BasicOS

The objective of the project is to program a new file system that can handle a "no space left on device" error: this new file system you are going to implement assumes that, when the file system is full, the file system deletes the oldest files until it can store the new file.

## Usage
```
git clone git@gitlab.eurecom.fr:ghaleb/basicos.git
cd basicos/src
make
./bin/myfs
```

## Example for write
```
myfs /tmp/FS write ./mylovelyfile /internaldirectory1/foo
```

## Structure 
```
|**Superblock**|  **Inodes** | **Datablocks**|
|--------------|-------------|---------------|
|  Fixed	#  | Fixed #	 | Variable #    |
|	 32B       | 10000 * 12B | x * 512B 	 |
```

### Repartition:
- William: ls, create
- Guillaume: read, remove
- Ahmed: write, size
### Authors: [@chieu](https://gitlab.eurecom.fr/chieu), [@ghaleb](https://gitlab.eurecom.fr/ghaleb) & [@ung](https://gitlab.eurecom.fr/ung)