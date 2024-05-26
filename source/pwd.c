#include "../include/main.h"

int pwd(DirectoryTree* dirTree, Stack* dirStack, char* cmd)
{
    if (!cmd)
        PrintPath(dirTree, dirStack);
    else if(cmd[0] == '-'){
        if(strcmp(cmd, "--help") == 0){
            printf("pwd: pwd [-LP]\n");
            printf("  Print the name of the current working directory.\n\n");
            
            printf("  Options:\n");
            printf("    -L\t print the value of $PWD if it names the current working\n");
            printf("  \t directory\n");
            printf("    -P\t print the physical direcrtory, without any symbolic links\n\n");
            
            printf("  By default, 'pwd' behaves as if '-L' were specified.\n\n");
            
            printf("  Exit status:\n");
            printf("  Returns 0 unless an invalid option is given or the current directory\n");
            printf("  cannot be read.\n");
        }
        else{
            printf("-bash: pwd: %s: invalid option\n", cmd);
            printf("pwd: usage: pwd [-LP]\n");
        }
        return -1;
    }
    else{
        printf("pwd: too many arguments.\n");
        return -1;
    }
    return 0;
}

int PrintPath(DirectoryTree* dirTree, Stack* dirStack)
{
    DirectoryNode* tmpNode = NULL;

    tmpNode = dirTree->current;
    if(tmpNode == dirTree->root){
        printf("/");
    }
    else{
        while(tmpNode->Parent != NULL){
            Push(dirStack, tmpNode->name);
            tmpNode = tmpNode->Parent;
        }
        while(IsEmpty(dirStack) == 0){
            printf("/");
            printf("%s",Pop(dirStack));
        }
    }
    printf("\n");

    return 0;
}