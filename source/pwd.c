#include "../include/main.h"

char* PrintDirectoryPath(DirectoryTree* dirTree) {
    DirectoryNode* current = dirTree->current;
    char* path = (char*)malloc(MAX_DIR * 2); // 동적 메모리 할당
    if (path == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    strcpy(path, "/"); // 루트 디렉토리로 초기화

    char* segments[MAX_DIR]; // 디렉토리 이름 저장 포인터
    int segmentCount = 0; // 세그먼트 수

    // 루트 디렉토리에 도달할 때까지 반복
    while (current != dirTree->root) {
        segments[segmentCount++] = current->name; // 디렉토리 이름을 배열에 저장
        current = current->Parent; // 상위 디렉토리로 이동
    }

    // 경로를 역순으로 연결하여 최종 경로 구성
    for (int i = segmentCount - 1; i >= 0; --i) {
        strncat(path, segments[i], MAX_DIR * 2 - strlen(path) - 1);
        if (i > 0) { // 마지막 세그먼트 뒤에는 슬래시를 추가하지 않음
            strncat(path, "/", MAX_DIR * 2 - strlen(path) - 1);
        }
    }

    return path;
}

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
        else if (strcmp(cmd,"--help") == 0) {
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