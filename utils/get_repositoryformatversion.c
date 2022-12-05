#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
