#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include "utils/utils.h"

struct repository
{
    char *worktree;
    char *gitdir;
    char *conf;
};


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