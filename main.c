#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ini.h"

struct repository{
    char* worktree;
    char* gitdir;
    char* conf;
};


struct repository init_repo(char* path, int force){
    struct repository repo;
    repo.worktree = path;
    repo.gitdir = strcat(path,path[strlen(path)-1]=='/' ? "" : "/" ".git");
    
    return repo;
};

char* get_repositoryformatversion(const char* path, char* repositoryformatversion) {
    int i;
    int j;
    FILE* ptr;
    char ch;
    ptr = fopen(path,"r");

    if(ptr == NULL) {
        printf("Can't open the file \n");
    }
    
    i=0;
    j=0;
    char key[] = "repositoryformatversion";
    int found = 0;
    do{
        if(i==strlen(key)){found=1;}

        char ch = fgetc(ptr);

        if(found==0){
            if(ch==key[i]){i++;}
            else if(i>0) {i=0;}
        }

        else if(found==1){
            if(ch==' ' || ch=='='){continue;}
            else if(ch=='\n'){break;}
            else{
                repositoryformatversion[j++]=ch;
            }
        }

    }while(ch!=EOF);

    fclose(ptr);
    return repositoryformatversion;
}

int main(int argc, char** argv){
    char repositoryformatversion[100];
    get_repositoryformatversion("./.git/config",repositoryformatversion);
    return 1;
}