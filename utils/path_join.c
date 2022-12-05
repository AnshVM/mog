#include <stdio.h>
#include <string.h>

char* path_join(char* destination, const char* path1, const char* path2){

    char* dir_sep = "/";
#ifdef WIN32
    dir_sep[0] = '\\';
#endif

    if(path1==NULL && path2==NULL){
        strcpy(destination,"");
    }
    else if(path1==NULL){
        strcpy(destination,path2);
    }
    else if(path2==NULL){
        strcpy(destination,path1);
    }
    else{
        strcpy(destination,path1);
        if(path1[strlen(path1)-1]!=dir_sep[0]){
            strcat(destination,dir_sep);
        }
        strcat(destination,path2); 
    }
    return destination;
}