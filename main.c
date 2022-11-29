#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

struct repository
{
    char *worktree;
    char *gitdir;
    char *conf;
};


char* get_repositoryformatversion(const char *path)
{
    int i;
    int j;
    FILE *ptr;
    char ch;
    char* repositoryformatversion = (char*)malloc(sizeof(char)*100); 
    ptr = fopen(path, "r");

    if (ptr == NULL)
    {
        return NULL;
    }

    i = 0;
    j = 0;

    char key[] = "repositoryformatversion";
    int found = 0;
    do
    {
        if (i == strlen(key))
        {
            found = 1;
        }
        char ch = fgetc(ptr);

        if (found == 0)
        {
            if (ch == key[i])
            {
                i++;
            }
            else if (i > 0)
            {
                i = 0;
            }
        }

        else if (found == 1)
        {
            if (ch == ' ' || ch == '=')
            {
                continue;
            }
            else if (ch == '\n')
            {
                break;
            }
            else
            {
                repositoryformatversion[j++] = ch;
            }
        }

    } while (ch != EOF);

    fclose(ptr);
    return repositoryformatversion;
}

struct repository init_repo(const char *path, int force)
{
    struct repository repo;

    repo.worktree = (char *)malloc(strlen(path) + 2);
    strcpy(repo.worktree, path);
    if (path[strlen(path) - 1] != '/')
    {
        strcat(repo.worktree, "/");
    }

    const char *dotgit = ".git/";
    repo.gitdir = (char *)malloc(strlen(repo.worktree) + strlen(dotgit) + 1);
    strcpy(repo.gitdir, repo.worktree);
    strcat(repo.gitdir, dotgit);

    DIR *dotgitdir = opendir(repo.gitdir);

    if(!(force==1 || dotgitdir)){
        printf("Not a Git repository: %s",path);
        exit(1);
    }

    const char* CONFIG = "config";
    char* gitconfig = (char*)malloc(strlen(repo.gitdir)+strlen(CONFIG)+1);
    strcpy(gitconfig,repo.gitdir);
    strcat(gitconfig,CONFIG);

    char* repositoryformatversion = get_repositoryformatversion(gitconfig);
    const char* correct_repositoryformatversion = "0";    

    if(force==0 && strcmp(repositoryformatversion,correct_repositoryformatversion)!=0){
        printf("Unsupported repositoryformatversion %s\n",repositoryformatversion);
        exit(1);
    }

    free(gitconfig);
    free(repositoryformatversion);

    return repo;
};

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

char* repo_path(struct repository repo, const char* path){
    int len = strlen(repo.gitdir) + strlen(path) + 2;
    char destination[len];
    return path_join(destination,repo.gitdir,path);
}

int main(int argc, char **argv)
{
    char repositoryformatversion[100];
    get_repositoryformatversion("./.git/config");
    struct repository new_repo = init_repo(".", 0);
    printf("%s\n",new_repo.gitdir);
    printf("%s\n",new_repo.worktree);
    printf("%s\n",repo_path(new_repo,"someshitfiles"));

}