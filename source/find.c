#include "../include/main.h"

//#define MAX_THREAD 10
//#define MAX_LENGTH 1024

//directory.h   getDir >> getDirectory
//char* getDirectory(const char* fullPath) {
//    char* DirectoryPath = (char*)malloc(MAX_DIR);
//    if (DirectoryPath == NULL) {
//        return NULL;  // 메모리 할당 실패 시 NULL 반환
//    }
//
//    // strrchr 함수를 사용하여 경로에서 마지막 '/' 찾기
//    const char* lastSlash = strrchr(fullPath, '/');
//    if (lastSlash == NULL || lastSlash == fullPath) {
//        free(DirectoryPath);
//        return NULL;  // '/'가 없거나 맨 처음에만 있는 경우
//    }
//
//    // 마지막 '/' 이전까지의 문자열을 복사
//    int pathLength = lastSlash - fullPath;
//    strncpy(DirectoryPath, fullPath, pathLength);
//    DirectoryPath[pathLength] = '\0'; // 문자열 종료 지점 명시
//
//    return DirectoryPath;
//}
//cd.h에 있는데 directory.h로   isexitdir(함수명) >> FindDirectoryNode
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


//cd.h
//int ChangeDirectory(DirectoryTree* dirTree, char* dirPath) {
//    // 변수 선언
//    DirectoryNode* tempNode = NULL;
//    DirectoryNode* savedNode = dirTree->current;  // 현재 디렉토리 노드를 임시 변수에 저장
//    char tempPath[MAX_DIR];
//    char* command = NULL;
//
//    // 현재 디렉토리 ('.')일 경우: 아무 작업도 하지 않음
//    if (strcmp(dirPath, ".") == 0) {
//        return 0;
//    }
//
//    // 상위 디렉토리로 이동하는 경우 ('..')
//    if (strcmp(dirPath, "..") == 0) {
//        if (dirTree->current != dirTree->root) { // 현재 디렉토리가 루트 디렉토리가 아니면 상위 디렉토리로 이동
//            dirTree->current = dirTree->current->Parent;
//        }
//        return 0;
//    }
//
//    // 경로를 tempPath에 복사
//    strncpy(tempPath, dirPath, MAX_DIR - 1); // 문자열 복사
//    tempPath[MAX_DIR - 1] = '\0';
//
//    // 최상위 디렉토리일 경우
//    if (strcmp(dirPath, "/") == 0) {
//        dirTree->current = dirTree->root; // 현재 디렉토리 = 루트 디렉토리
//        return 0;
//    }
//
//    // 절대 경로인 경우
//    if (dirPath[0] == '/') {
//        dirTree->current = dirTree->root; // 현재 디렉토리 = 루트 디렉토리
//        command = strtok(tempPath + 1, "/"); // 첫번째 디렉토리 이름 추출
//    }
//    else {  // 상대 경로인 경우
//        command = strtok(tempPath, "/"); // 첫번째 디렉토리 이름 추출
//    }
//
//    // 경로를 하나씩 탐색하며 이동
//    while (command != NULL) {
//        // 하위 디렉토리로 이동하는 경우
//        tempNode = FindDirectoryNode(dirTree, command, 'd');// 해당 이름의 디렉토리가 존재하면 이동
//        if (tempNode != NULL) {
//            dirTree->current = tempNode;
//        }
//        else {
//            // 디렉토리가 존재하지 않을 경우
//            dirTree->current = savedNode; // 현재 디렉토리 복원
//            return -1;
//        }
//        command = strtok(NULL, "/");
//    }
//
//    return 0;
//}


//directory.h (변수명, 약간의 수정) 함수명 ReadDir에서 변경
int ReadDirectory(DirectoryTree* dirTree, char* line, char* dirName)
{
    char* str; // 문자열 포인터
    char firstSegment[MAX_NAME]; // 첫번째 segment를 저장할 버퍼
    char found = 0;


    str = strtok(line, " "); // 문자열을 띄어쓰기 단위로 분리
    if (str != NULL) {
        strncpy(firstSegment, str, MAX_NAME);
        firstSegment[MAX_NAME - 1] = '\0'; // 안전한 종료를 위해 널 문자 추가
    }

    for (int count = 0; count < 10; count++) {  // 10번 반복
        str = strtok(NULL, " "); // 다음 문자열 분리
    }
    //마지막 문자열에 해당하는 부분에 도착
    if (str != NULL) { // 문자열이 남아 있는 경우
        str[strlen(str) - 1] = '\0'; // 문자열 끝에 NULL 추가, 문자열 종료, 개행문자제거 
        char* found = strstr(str, dirName);// 대소문자 구분 없이 문자열 검색, 일치하는 부분 문자열의 시작주소 반한
        if (found) { // dirName과 일치하는 문자열을 찾은 경우
            if (strcmp(str, "/") == 0) {
                printf("/%s\n", firstSegment); // 루트 디렉토리인 경우 경로 출력
            }
            else {
                printf("%s/%s\n", found, firstSegment);  //루트 디렉토리가 아닌경우, found와 firstSegment 결합, 경로 출력
            }
        }
    }
    return 0;
}

//directory.h (변수명, 약간의 수정) 함수명 FindDir에서 변경
void FindDirectory(DirectoryTree* dirTree, char* dirName)     //Directory.txt 파일을 열고 지정된 디렉토리 이름을 검색
{
    FILE* file = fopen("Directory.txt", "r"); //directory.txt 파일을 읽기모드로 열고
    if (!file) {
        perror("No such file or directory");
        return;
    }
    char line[MAX_LENGTH]; //파일에서 읽은 각 줄을 저장할 임시 버퍼 
    while (fgets(line, sizeof(line), file)) { //파일을 한 줄씩 읽고 line에 저장, ReadDirectory를 호출하여 각 line에서 디렉토리 이름을 검색하고 일치하는 경로 출력
        ReadDirectory(dirTree, line, dirName);
    }
    fclose(file);
}


// 1) 명령어에 '/'가 포함되지 않은 경우, 위치한 현재 디렉토리에서 파일이나 디렉토리 검색
// 2) 명령어에 '/'가 포함되어 있는 경우, 파일이나 디렉토리 검색
// 2-1) 경로가 잘못됐을 경우,
// 2-2) 경로가 올바르나, 파일이나 디렉토리가 없을경우
void* FindThread(void* arg) {
    ThreadTree* threadTree = (ThreadTree*)arg; // 스레드 정보와 명령을 포함하는 구조체
    DirectoryTree* dirTree = threadTree->threadTree; // 디렉토리 트리 접근
    char* cmd = threadTree->command; // 실행할 명령
    char fullPath[MAX_DIR]; // 전체 경로를 저장할 버퍼
    char* fileName; // 파일 이름
    char* dirPath; // 디렉토리 경로
    int dirCheck; // 디렉토리 변경 성공 여부 확인
    DirectoryNode* currentNode = dirTree->current;
    strncpy(fullPath, cmd, MAX_DIR); // 명령어에서 전체 경로 복사
    fullPath[MAX_DIR - 1] = '\0'; // 널 종료 문자 보장

    // 파일 이름과 디렉토리 경로 분리
    fileName = strrchr(fullPath, '/');
    if (fileName) {
        fileName++; // '/' 다음 문자로 파일 이름 시작
        dirPath = fullPath;
        *(fileName - 1) = '\0'; // 파일 이름 앞에서 문자열 종료로 디렉토리 경로 설정
    }
    else {
        fileName = fullPath; // '/'가 없는 경우, 전체 명령이 파일 이름
        dirPath = ".";
    }

    // 필요한 경우 디렉토리 변경
    if (strcmp(dirPath, ".") != 0) {
        dirCheck = ChangeDirectory(dirTree, dirPath);
        if (dirCheck != 0) {
            printf("find: '%s': No such file or directory.\n", dirPath);
            dirTree->current = currentNode;
            pthread_exit(NULL);
        }
    }

    // 파일 또는 디렉토리 존재 여부 확인
    if (!FindDirectoryNode(dirTree, fileName, 'd') && !FindDirectoryNode(dirTree, fileName, 'f')) {
        printf("find: '%s': No such file or directory.\n", fileName);
        dirTree->current = currentNode;
        pthread_exit(NULL);
    }

    printf("%s\n", cmd); // 검색 결과 출력
    FindDirectory(dirTree, cmd);
    pthread_exit(NULL);

}
int find(DirectoryTree* dirTree, char* cmd)
{
    char* command; //명령어 저장 포인터 
    pthread_t ThreadArr[MAX_THREAD]; //thread 식별자 배열
    ThreadTree ThreadTree[MAX_THREAD]; // thread별 작업 정보 배열 / threadtree 구조체 배열

    int ThreadCount = 0; // 생성된 thread 수
    //find . and find and find -- 인 경우, 현재 디렉토리에서 SearchDir호출
    if (cmd == NULL || strcmp(cmd, ".") == 0 || strcmp(cmd, "--") == 0) {
        FindDirectory(dirTree, dirTree->current->name); //현재 디렉토리 검색
        return 0;
    }
    else if (cmd[0] == '-') { //명령어가 대시(-)로 시작하면(옵션인 경우)
        if (strcmp(cmd, "--help") == 0) {//, 명령어가 --help인지 확인하고 사용법과 옵션에 대한 도움말을 출력
            printf("Usage: find [OPTION] [path...] [expression]\n\n");
            printf("    Search for files in a directory hierarchy.\n\n");
            printf("    Options:\n");
            printf("       .         Search for files in the current directory\n");
            printf("       --        Search for files in the current directory\n");
            printf("       --help    display this help and exit\n");
            printf("default path is the current directory; default expression is -print\n");

            return -1;
        }
        else {  //유효하지 않은 옵션인 경우 오류메세지와 도움말 출력
            char* invalid_option = strchr(cmd, '-');
            printf("find: unknown predicate '%s'\n", invalid_option);  // 오류 메시지
            printf("Try 'find --help' for more information.\n");  // 도움말 안내
            return -1;
        }
    }
    else //threadTree 배열을 반복하며, 각 명령어에 대해 새로운 스레드를 생성하고(pthread_create), 각 스레드가 완료될 때까지 기다림(pthread_join).
    {
        command = strtok(cmd, " "); //cmd에서 첫 번째 명령어 분리
        ThreadTree[ThreadCount].threadTree = dirTree; // 현재 디렉토리 트리 설정
        ThreadTree[ThreadCount++].command = cmd; //첫 번째 명령어 설정
    }
    while (command != NULL) {   // 명령어가 남아있는 동안 반복 ( //멀티스레드 작업을 위해 파일이름마다 스레드배열안에 정보를 저장)
        ThreadTree[ThreadCount].threadTree = dirTree; // 현재 디렉토리 트리 설정
        ThreadTree[ThreadCount++].command = command; // 명령어 설정
        command = strtok(NULL, " "); // 다음 명령어 분리
    }
    for (int i = 0; i < ThreadCount; i++) { // 모든 스레드를 생성
        pthread_create(&ThreadArr[i], NULL, FindThread, (void*)&ThreadTree[i]);
    }
    for (int i = 0; i < ThreadCount; i++) { // 모든 스레드가 종료될 때까지 기다림
        pthread_join(ThreadArr[i], NULL);
    }

    return 0;


}