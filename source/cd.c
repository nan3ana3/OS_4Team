#include "../include/main.h"

char previousPath[MAX_DIR * 2] = ""; // 이전 경로를 저장할 변수

int ChangeDirectory(DirectoryTree* dirTree, char* dirPath) {
    // 변수 선언
    DirectoryNode* tempNode = NULL;
    DirectoryNode* savedNode = dirTree->current;  // 현재 디렉토리 노드를 임시 변수에 저장
    char tempPath[MAX_DIR];
    char* command = NULL;

    // 현재 디렉토리 ('.')일 경우: 아무 작업도 하지 않음
    if (strcmp(dirPath, ".") == 0) {
        return 0;
    }

    // 상위 디렉토리로 이동하는 경우 ('..')
    if (strcmp(dirPath, "..") == 0) {
        if (dirTree->current != dirTree->root) { // 현재 디렉토리가 루트 디렉토리가 아니면 상위 디렉토리로 이동
            dirTree->current = dirTree->current->Parent;
        }
        return 0;
    }

    // 경로를 tempPath에 복사
    strncpy(tempPath, dirPath, MAX_DIR - 1); // 문자열 복사
    tempPath[MAX_DIR - 1] = '\0';

    // 최상위 디렉토리일 경우
    if (strcmp(dirPath, "/") == 0) {
        dirTree->current = dirTree->root; // 현재 디렉토리 = 루트 디렉토리
        return 0;
    }

    // 절대 경로인 경우
    if (dirPath[0] == '/') {
        dirTree->current = dirTree->root; // 현재 디렉토리 = 루트 디렉토리
        command = strtok(tempPath + 1, "/"); // 첫번째 디렉토리 이름 추출
    }
    else {  // 상대 경로인 경우
        command = strtok(tempPath, "/"); // 첫번째 디렉토리 이름 추출
    }

    // 경로를 하나씩 탐색하며 이동
    while (command != NULL) {
        // 하위 디렉토리로 이동하는 경우
        tempNode = FindDirectoryNode(dirTree, command, 'd');// 해당 이름의 디렉토리가 존재하면 이동
        if (tempNode != NULL) {
            dirTree->current = tempNode;
        }
        else {
            // 디렉토리가 존재하지 않을 경우
            dirTree->current = savedNode; // 현재 디렉토리 복원
            return -1;
        }
        command = strtok(NULL, "/");
    }

    return 0;
}

int cd(DirectoryTree* dirTree, char* cmd) {
    DirectoryNode* tempNode = NULL;
    char temp[MAX_DIR];
    char* currentPath;
    int check;
    // 현재 경로를 저장하여 이전에 위치한 경로로 사용
    currentPath = PrintDirectoryPath(dirTree);
    // cmd . or cmd 
    if (cmd == NULL || strcmp(cmd, ".") == 0) {
        check = ChangeDirectory(dirTree, cmd);
    } //cmd ~ : 홈 디렉토리로 이동
    else if (strcmp(cmd, "~") == 0) {
        strcpy(temp, userList->current->dir);
        check = ChangeDirectory(dirTree, temp);
    }
    else if (strcmp(cmd, "/") == 0) {
        check = ChangeDirectory(dirTree, cmd);
    }
    else if (strcmp(cmd, "..") == 0) {
        check = ChangeDirectory(dirTree, cmd);
    }
    else if (cmd[0] == '-') //옵션이 있을경우 
    {
        if (strcmp(cmd, "--help") == 0)
        {
            printf("Usage: cd [OPTION] [DIRECTORY]\n");
            printf("    Change the shell working directory.\n\n");
            printf("    Change the current directory to DIR.  The default DIR is the value of the Home shell variable.\n\n");
            printf("    Options:\n");
            printf("       ~     Go to the home directory of the current user\n");
            printf("       -     Switch to the previous directory\n");
            printf("       /     Change to the root directory\n");
            printf("       .     Remain in the current directory\n");
            printf("       ..    Move up to the parent directory\n");
            printf("       --help     display this help and exit\n");
            free(currentPath);
            return 0;
        }
        else if (strcmp(cmd, "-") == 0)
        {
            if (previousPath[0] == '\0') {
                printf("OWD PWD NOT SET\n");
                free(currentPath);
                return -1;
            }
            printf("%s\n", previousPath);
            check = ChangeDirectory(dirTree, previousPath);
        }
        else
        {
            // 그 외의 옵션들 에러 처리
            printf("bash: cd: %s: invalid option\n", cmd);
            printf("Try 'cd ?help' for more information.\n");
            free(currentPath);
            return -1;

        }
    }
    else //옵션이 없을 경우 
    {
        tempNode = FindDirectoryNode(dirTree, cmd, 'd');
        if (tempNode != NULL) {
            if (HasPermission(tempNode, 'x') != 0) {       //접근권한이 거부되어 있을 경우
                printf("cd: %s: Permission denied\n", cmd);
                free(currentPath);
                return -1;
            }
        }
        else {
            // 디렉토리를 찾지 못한 경우
            printf("cd: %s: No such file or directory\n", cmd);
            free(currentPath);
            return -1;
        }
        check = ChangeDirectory(dirTree, cmd);

    }

    // 이전 경로 업데이트
    if (check == 0) //디렉토리 변경이 성공한 경우,
    {
        strncpy(previousPath, currentPath, sizeof(previousPath) - 1);
        previousPath[sizeof(previousPath) - 1] = '\0';
    }
    free(currentPath);

    return 0;
}
