#include "../include/main.h"

void pwd(DirectoryTree* dirTree, char* cmd) {
    if (cmd == NULL || strcmp(cmd, "") == 0)
    {
        // �⺻ ��ɾ� pwd
        char* path = PrintDirectoryPath(dirTree);
        if (path != NULL) {
            printf("%s\n", path);
            free(path);
        }
    }
    else if (cmd[0] == '-')
    {
        if (strcmp(cmd, "-") == 0 || strcmp(cmd, "--") == 0)
        {
            // �⺻ ��ɾ� pwd, pwd -, pwd -- ��� ���� ��� ���
            char* path = PrintDirectoryPath(dirTree);
            if (path != NULL) 
            {
                printf("%s\n", path);
                free(path);
            }
        }
        else if (strcmp(cmd, "--help") == 0) {
            // pwd --help
            printf("Usage: pwd [OPTION]\n");
            printf("    Print the name of the current working directory.\n\n");
            printf("    Options:\n");
            printf("       -         print the name of the current working directory\n");
            printf("       --        print the name of the current working directory\n");
            printf("       --help    display this help and exit\n");
        }
        else 
        {
            // �߸��� �ɼ� ���� �޽��� ��� ex)pwd -aa
            printf("bash: pwd: %s: invalid option\n", cmd);
            printf("Try 'pwd --help' for more information.\n");
        }
    }
    else
    { 
        char* path = PrintDirectoryPath(dirTree);
            if (path != NULL) 
            {
                printf("%s\n", path);
                free(path);
            }
     //pwd �� �����̿����� ��� x ���� ���丮 ��ġ ���
    }
}