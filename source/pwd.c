#include "../include/main.h"

void pwd(DirectoryTree* dirTree, char* cmd) {
    if (cmd == NULL || strcmp(cmd, "") == 0)
    {
        // 기본 명령어 pwd
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
            // 기본 명령어 pwd, pwd -, pwd -- 모두 현재 경로 출력
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
            // 잘못된 옵션 에러 메시지 출력 ex)pwd -aa
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
     //pwd 에 무엇이오든지 상관 x 현재 디렉토리 위치 출력
    }
}