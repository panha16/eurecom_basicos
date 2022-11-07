#include<stdio.h>
#include<string.h> 
#include<stdlib.h>  
#include<fcntl.h>   
#include<sys/stat.h>    
#include<unistd.h>  

int main(int argc,const char **argv)
{
    //variable declaration
    int iFd = 0;
    char *chDirName = NULL;
    char *chFileName = NULL;
    char *chFullPath = NULL;
    struct stat sfileInfo;

    //Argument Validation
    if(argc != 3)
    {
        printf("[ERROR] Insufficient Arguments\n");
        return(-1);
    }

    //argument processing
    chDirName = (char *)malloc(sizeof(char));
    chFileName = (char *)malloc(sizeof(char));
    chFullPath = (char *)malloc(sizeof(char));
    chDirName = strcpy(chDirName,argv[1]);
    chFileName = strcpy(chFileName,argv[2]);

    //create full path of file
    sprintf(chFullPath,"%s/%s",chDirName,chFileName);

    //check directory exists or not
    if(stat(chDirName,&sfileInfo) == -1)
    {
        mkdir(chDirName);
        printf("[INFO] Directory Created: %s\n",chDirName);
    }

    //create file inside given directory
    iFd = creat(chFullPath,0644);

    if(iFd == -1)
    {
        printf("[ERROR] Unable to create file: %s\n",chFullPath);
        free(chDirName);
        free(chFileName);
        free(chFullPath);
        return(-1);
    }

    printf("[INFO] File Created Successfully : %s\n",chFullPath);

    //close resources
    close(iFd);
    free(chDirName);
    free(chFileName);
    free(chFullPath);

    return(0);
}
