#include "../include/main.h"

char previousPath[MAX_DIR * 2] = ""; // 이전 경로를 저장할 변수

////permission.h
//int CheckPermission(const int* permissions, char pms, int index) {
//    switch (pms) {
//    case 'r': return permissions[index] ? 0 : -1; // 읽기 권한 확인
//    case 'w': return permissions[index + 1] ? 0 : -1; // 쓰기 권한 확인
//    case 'x': return permissions[index + 2] ? 0 : -1; // 실행 권한 확인
//    default: return -1; // 잘못된 권한 요청
//    }
//}
////permission.h
//int HasPermission(DirectoryNode* dirNode, char pms)
//{
//    // userList나 current 사용자가 NULL인지 확인
//    if (userList == NULL || userList->current == NULL) {
//        return -1; // 적절한 에러 코드 반환
//    }
//
//    // 관리자 (루트 사용자)는 모든 권한을 가짐
//    if (userList->current->UserID == 0) {
//        return 0;
//    }
//    // 소유자의 권한을 확인
//    if (userList->current->UserID == dirNode->UserID) {
//        return CheckPermission(dirNode->permission, pms, 0);
//    }
//
//    // 그룹의 권한을 확인
//    if (userList->current->GroupID == dirNode->GroupID) {
//        return CheckPermission(dirNode->permission, pms, 3);
//    }
//
//    // 기타 사용자의 권한을 확인
//    return CheckPermission(dirNode->permission, pms, 6);
//}
//
//DirectoryNode* FindDirectoryNode(DirectoryTree* dirTree, char* dirName, char type) {
//    DirectoryNode* currentNode = dirTree->current->LeftChild; // 현재 디렉토리의 첫 번째 자식 노드로 설정
//
//    // 모든 자식 노드를 탐색
//    while (currentNode != NULL) {
//        // 디렉토리 이름과 유형이 일치하면 노드를 반환
//        if (strcmp(currentNode->name, dirName) == 0 && currentNode->type == type) {
//            return currentNode;
//        }
//        // 다음 형제 노드로 이동
//        currentNode = currentNode->RightSibling;
//    }
//    // 일치하는 노드를 찾지 못하면 NULL 반환
//    return NULL;
//}


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

////pwd.h
//char* PrintDirectoryPath(DirectoryTree* dirTree) {
//    DirectoryNode* current = dirTree->current;
//    char* path = (char*)malloc(MAX_DIR * 2); // 동적 메모리 할당
//    if (path == NULL) {
//        return NULL; // 메모리 할당 실패 시 NULL 반환
//    }
//    strcpy(path, "/"); // 루트 디렉토리로 초기화
//
//    char* segments[MAX_DIR]; // 디렉토리 이름 저장 포인터
//    int segmentCount = 0; // 세그먼트 수
//
//    // 루트 디렉토리에 도달할 때까지 반복
//    while (current != dirTree->root) {
//        segments[segmentCount++] = current->name; // 디렉토리 이름을 배열에 저장
//        current = current->Parent; // 상위 디렉토리로 이동
//    }
//
//    // 경로를 역순으로 연결하여 최종 경로 구성
//    for (int i = segmentCount - 1; i >= 0; --i) {
//        strncat(path, segments[i], MAX_DIR * 2 - strlen(path) - 1);
//        if (i > 0) { // 마지막 세그먼트 뒤에는 슬래시를 추가하지 않음
//            strncat(path, "/", MAX_DIR * 2 - strlen(path) - 1);
//        }
//    }
//
//    return path;
//}

int cd(DirectoryTree* dirTree, char* cmd) {
    DirectoryNode* tempNode = NULL;
    char temp[MAX_DIR];
    char* currentPath;
    int check;
    // 현재 경로를 저장하여 이전에 위치한 경로로 사용
    currentPath = PrintDirectoryPath(dirTree);
    // 자신의 홈 디렉토리로 이동
    if (cmd == NULL || strcmp(cmd, "~") == 0) {
        strcpy(temp, userList->current->dir);
        check = ChangeDirectory(dirTree, temp);
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
            cmd = strtok(cmd, "-");     // 그 외의 옵션들 에러 처리
            printf("bash: cd: %s: invalid option\n", cmd);
            printf("Try 'cd --help' for more information.\n");
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


