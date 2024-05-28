#include "../include/main.h"

FILE* User;
time_t Utime;
struct tm* time_info;
UserList* userList;

//현재 시간 계산 , 유닉스 타임을 로컬 시간으로 변환
void SetCurrentTime(UserNode* tmpNode) {
    time_t Utime = time(NULL);  // 초 단위로 유닉스 타임 가져오기
    struct tm* time_info = localtime(&Utime);

    tmpNode->year = time_info->tm_year + 1900;  // 현재 연도 설정
    tmpNode->month = time_info->tm_mon + 1;     // 현재 월 설정
    tmpNode->wday = time_info->tm_wday;         // 현재 요일 설정
    tmpNode->mday = time_info->tm_mday;         // 현재 일 설정
    tmpNode->hour = time_info->tm_hour;         // 현재 시간 설정
    tmpNode->minute = time_info->tm_min;        // 현재 분 설정
    tmpNode->sec = time_info->tm_sec;           // 현재 초 설정
}
//사용자 리스트를 초기화 및 'root' 사용자 생성 함수
UserList* InitializeUser()
{
    UserList* returnList = (UserList*)malloc(sizeof(UserList));  // 사용자 리스트를 위한 메모리 할당
    UserNode* tmpNode = (UserNode*)malloc(sizeof(UserNode));    // 사용자 노드를 위한 메모리 할당
    strncpy(tmpNode->name, "root", MAX_NAME);  // 사용자 이름 root
    strncpy(tmpNode->dir, "/", MAX_NAME);      // 홈 디렉토리  /
    SetCurrentTime(tmpNode);

    tmpNode->link = NULL;  // 다음 노드 초기화
    returnList->head = tmpNode;  // 리스트의 헤드를 설정
    returnList->tail = tmpNode;  // 리스트의 꼬리를 설정
    returnList->current = tmpNode;  // 현재 노드를 설정
    returnList->topUID = 0;  // topUID, topgGID 0으로 설정
    returnList->topGID = 0;  // 

    return returnList;  // 초기화된 사용자 리스트 반환
}

void WriteUser(UserList* userList, UserNode* userNode) {
    // 현재 시간 설정
    SetCurrentTime(userList->current);

    // 사용자 정보를 파일에 기록
    fprintf(User, "%s %d %d %d %d %d %d %d %d %d %s\n",
        userNode->name, userNode->UserID, userNode->GroupID, userNode->year,
        userNode->month, userNode->mday, userNode->wday, userNode->hour,
        userNode->minute, userNode->sec, userNode->dir);

    // 다음 사용자 노드가 있을 경우 재귀적으로 호출
    if (userNode->link != NULL) {
        WriteUser(userList, userNode->link);
    }
}

void SaveUserList(UserList* userList)
{
    // "User.txt" 파일을 쓰기 모드로 열기
    User = fopen("User.txt", "w");

    // 사용자 리스트를  파일에 저장
    WriteUser(userList, userList->head);

    fclose(User);
}
//사용자 정보를 읽어와 사용자 노드 생성하고, 사용자 리스트에 추가
int ReadUser(UserList* userList, char* tmp)
{
    UserNode* tempNode = (UserNode*)malloc(sizeof(UserNode));  // 새 사용자 노드를 위한 메모리 할당

    tempNode->link = NULL;  // 다음 노드 초기화

    // 사용자 정보를 공백을 기준으로 파싱하여 tmpNode에 저장
    char* data = strtok(tmp, " ");
    strncpy(tempNode->name, data, MAX_NAME);
    data = strtok(NULL, " ");
    tempNode->UserID = atoi(data);
    data = strtok(NULL, " ");
    tempNode->GroupID = atoi(data);
    data = strtok(NULL, " ");
    tempNode->year = atoi(data);
    data = strtok(NULL, " ");
    tempNode->month = atoi(data);
    data = strtok(NULL, " ");
    tempNode->mday = atoi(data);
    data = strtok(NULL, " ");
    tempNode->wday = atoi(data);
    data = strtok(NULL, " ");
    tempNode->hour = atoi(data);
    data = strtok(NULL, " ");
    tempNode->minute = atoi(data);
    data = strtok(NULL, " ");
    tempNode->sec = atoi(data);
    data = strtok(NULL, " ");

    data[strlen(data) - 1] = '\0';
    strncpy(tempNode->dir, data, MAX_DIR); //homeDir 설정

    // 사용자 리스트의 헤드와 테일을 설정 루트 사용자 인경우와 아닌경우로
    if (strcmp(tempNode->name, "root") == 0) {
        userList->head = tempNode;
        userList->tail = tempNode;
    }
    else {
        userList->tail->link = tempNode;
        userList->tail = tempNode;
    }

    return 0;  // 성공적으로 완료되었음을 반환
}
//사용자 리스트를 파일에서 로드하는 함수
UserList* LoadUserList()
{
    UserList* userList = (UserList*)malloc(sizeof(UserList));
    char tmp[MAX_LENGTH];

    User = fopen("User.txt", "r");

    while (fgets(tmp, MAX_LENGTH, User) != NULL) {
        ReadUser(userList, tmp);
    }

    fclose(User);

    userList->current = NULL;

    return userList;
}
UserNode* FindUserNode(UserList* userList, char* userName)
{
    UserNode* currentNode = userList->head;
    // 모든 노드를 탐색
    while (currentNode != NULL) {
        if (strcmp(currentNode->name, userName) == 0) {
            return currentNode;
        }
        // 다음 노드로 이동
        currentNode = currentNode->link;
    }
    // 일치하는 노드를 찾지 못하면 NULL 반환
    return NULL;
}
// 그룹 ID와 유저 ID를 기반으로 사용자 리스트에서 일치하는 ID를 가진 사용자 노드를 찾고, 해당 사용자 노드의 이름을 반환 
char* FindUID(DirectoryNode* dirNode)
{
    UserNode* currentNode = userList->head;

    while (currentNode != NULL) {
        if (currentNode->UserID == dirNode->UserID) {
            return currentNode->name;
        }
        currentNode = currentNode->link;
    }
    return NULL;
}

char* FindGID(DirectoryNode* dirNode)
{
    UserNode* currentNode = userList->head;


    while (currentNode != NULL) {
        if (currentNode->GroupID == dirNode->GroupID)
            return currentNode->name;
        currentNode = currentNode->link;
    }
    return NULL;
}
//Login 함수는 사용자로부터 로그인할 사용자 이름을 입력받고, 해당 사용자가 존재하면 현재 사용자로 설정.또한 로그인한 사용자의 홈 디렉토리로 이동
void Login(UserList* userList, DirectoryTree* dirTree)
{
    UserNode* currentNode = NULL;
    char input[MAX_NAME];
    char homeDir[MAX_DIR];

    // 사용자 리스트의 모든 사용자 이름을 출력
    printf("User List: ");
    for (currentNode = userList->head; currentNode != NULL; currentNode = currentNode->link) {
        printf("%s ", currentNode->name);
    }
    printf("\n");

    // 사용자로부터 유효한 사용자 이름을 입력받음
    while (1) {
        printf("Enter username to login (or 'exit' to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';
        if (input == NULL) {
            printf("Input error. Please try again.\n");
            continue;
        }
        else if (strcmp(input, "exit") == 0) { // "exit" 입력 시 프로그램 종료
            printf("Exiting program.\n");
            exit(0);
        }
        currentNode = FindUserNode(userList, input);
        if (currentNode != NULL) {
            // 존재하는 사용자인 경우 현재 사용자로 설정
            userList->current = currentNode;
            printf("Login successful. Welcome, %s!\n", currentNode->name);
            break;
        }
        else {
            // 존재하지 않는 사용자일 경우 오류 메시지 출력
            printf("User '%s' does not exist. Please try again.\n", input);
        }
    }

    // 현재 사용자의 홈 디렉토리로 이동
    strncpy(homeDir, userList->current->dir, MAX_DIR);
    ChangeDirectory(dirTree, homeDir);
}
