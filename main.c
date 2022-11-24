#include <stdio.h>

int main(int argc, char** argv){
    int i=0;
    printf("Your args are:\n");
    for(i=0;i<argc;i++){
        printf("%d:%s\n",i+1,argv[i]);
    }
}