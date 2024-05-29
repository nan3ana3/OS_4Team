#include "../include/main.h"

// 사용자 리스트 초기화
UserList* InitializeUser()
{
    // 새로운 사용자 리스트와 사용자 노드 메모리 할당
    UserList* returnList = (UserList*)malloc(sizeof(UserList));
    UserNode* tmpNode = (UserNode*)malloc(sizeof(UserNode));

    // 현재 시간 가져오기
    time(&ltime);
    today = localtime(&ltime);

    // 루트 사용자 정보 설정
    strncpy(tmpNode->name, "root", MAX_NAME);
    strncpy(tmpNode->dir, "/", MAX_NAME);
    tmpNode->UserID = 0;
    tmpNode->GroupID = 0;
    tmpNode->year = today->tm_year + 1900;
    tmpNode->month = today->tm_mon + 1;
    tmpNode->wday = today->tm_wday;
    tmpNode->day = today->tm_mday;
    tmpNode->hour = today->tm_hour;
    tmpNode->minute = today->tm_min;
    tmpNode->sec = today->tm_sec;
    tmpNode->link= NULL;

    // 사용자 리스트 초기화
    returnList->head = tmpNode;
    returnList->tail = tmpNode;
    returnList->current = tmpNode;
    returnList->topUID = 0;
    returnList->topGID = 0;

    return returnList;
}

// 사용자 정보를 파일에 기록
void WriteUser(UserList* userList, UserNode* userNode)
{
    // 현재 시간 가져오기
    time(&ltime);
    today = localtime(&ltime);

    // 현재 사용자 정보 업데이트
    userList->current->year = today->tm_year + 1900;
    userList->current->month = today->tm_mon + 1;
    userList->current->wday = today->tm_wday;
    userList->current->day = today->tm_mday;
    userList->current->hour = today->tm_hour;
    userList->current->minute = today->tm_min;
    userList->current->sec = today->tm_sec;

    // 사용자 정보 파일에 기록
    fprintf(User, "%s %d %d %d %d %d %d %d %d %d %s\n",
        userNode->name, userNode->UserID, userNode->GroupID, userNode->year,
        userNode->month, userNode->wday, userNode->day, userNode->hour,
        userNode->minute, userNode->sec, userNode->dir);

    // 연결된 다음 사용자 노드도 기록
    if (userNode->link != NULL) {
        WriteUser(userList, userNode->link);
    }
}

// 사용자 리스트를 파일에 저장
void SaveUserList(UserList* userList)
{
    // 파일 열기
    User = fopen("User.txt", "w");

    // 사용자 리스트를 파일에 기록
    WriteUser(userList, userList->head);

    // 파일 닫기
    fclose(Directory);
}

// 파일에서 사용자 정보를 읽어와서 사용자 리스트에 추가
int ReadUser(UserList* userList, char* tmp)
{
    // 새로운 사용자 노드 메모리 할당
    UserNode* tmpNode = (UserNode*)malloc(sizeof(UserNode));
    char* user_infor;

    tmpNode->link = NULL;

    // 문자열에서 사용자 정보 추출
    user_infor = strtok(tmp, " ");
    strncpy(tmpNode->name, user_infor, MAX_NAME);
    user_infor = strtok(NULL, " ");
    tmpNode->UserID = atoi(user_infor);
    user_infor = strtok(NULL, " ");
    tmpNode->GroupID = atoi(user_infor);
    user_infor = strtok(NULL, " ");
    tmpNode->year = atoi(user_infor);
    user_infor = strtok(NULL, " ");
    tmpNode->month = atoi(user_infor);
    user_infor = strtok(NULL, " ");
    tmpNode->wday = atoi(user_infor);
    user_infor = strtok(NULL, " ");
    tmpNode->day = atoi(user_infor);
    user_infor = strtok(NULL, " ");
    tmpNode->hour = atoi(user_infor);
    user_infor = strtok(NULL, " ");
    tmpNode->minute = atoi(user_infor);
    user_infor = strtok(NULL, " ");
    tmpNode->sec = atoi(user_infor);
    user_infor = strtok(NULL, " ");
    user_infor[strlen(user_infor) - 1] = '\0';
    strncpy(tmpNode->dir, user_infor, MAX_DIR);

    // 사용자 리스트에 노드 추가
    if (strcasecmp(tmpNode->name, "root") == 0) {
        userList->head = tmpNode;
        userList->tail = tmpNode;
    } else {
        userList->tail->link = tmpNode;
        userList->tail = tmpNode;
    }
    return 0;
}

// 파일에서 사용자 리스트를 로드
UserList* LoadUserList()
{
    // 새로운 사용자 리스트 메모리 할당
    UserList* userList = (UserList*)malloc(sizeof(UserList));
    char tmp[MAX_LENGTH];

    // 파일 열기
    User = fopen("User.txt", "r");

    // 파일에서 사용자 정보를 읽어와서 사용자 리스트에 추가
    while (fgets(tmp, MAX_LENGTH, User) != NULL) {
        ReadUser(userList, tmp);
    }

    // 파일 닫기
    fclose(User);

    userList->current = NULL;

    return userList;
}

// 주어진 사용자 이름이 사용자 리스트에 존재하는지 확인
UserNode* IsExistUser(UserList* userList, char* userName)
{
    UserNode* returnUser = NULL;

    returnUser = userList->head;

    // 사용자 리스트를 순회하며 사용자 이름 확인
    while (returnUser != NULL) {
        if (strcasecmp(returnUser->name, userName) == 0)
            break;
        returnUser = returnUser->link;
    }

    return returnUser;
}

// 주어진 디렉토리 노드의 UID에 해당하는 사용자 이름 반환
char* GetUID(DirectoryNode* dirNode)
{
    UserNode* tmpNode = NULL;

    tmpNode = userList->head;
    while (tmpNode != NULL) {
        if (tmpNode->UserID == dirNode->UserID)
            break;
        tmpNode = tmpNode->link;
    }
    return tmpNode->name;
}

// 주어진 디렉토리 노드의 GID에 해당하는 그룹 이름 반환
char* GetGID(DirectoryNode* dirNode)
{
    UserNode* tmpNode = NULL;

    tmpNode = userList->head;
    while (tmpNode != NULL) {
        if (tmpNode->GroupID == dirNode->GroupID)
            break;
        tmpNode = tmpNode->link;
    }
    return tmpNode->name;
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

// 사용자 로그인 함수
void Login(UserList* userList, DirectoryTree* dirTree)
{
    UserNode* tmpNode = NULL;
    char userName[MAX_NAME];
    char tmp[MAX_DIR];

    tmpNode = userList->head;

    // 사용자 리스트 출력
    printf("Users: ");
    while (tmpNode != NULL) {
        printf("%s ", tmpNode->name);
        tmpNode = tmpNode->link;
    }
    printf("\n");

    // 로그인 반복문
    while (1) {
        printf("Login : ");
        fgets(userName, sizeof(userName), stdin);
        userName[strlen(userName) - 1] = '\0';
        if (strcmp(userName, "exit") == 0) {
            exit(0);
        }
        tmpNode = IsExistUser(userList, userName);
        if (tmpNode != NULL) {
            userList->current = tmpNode;
            break;
        }
        printf("'%s' User does not exist\n", userName);
    }

    // 로그인한 사용자의 디렉토리로 이동
    strcpy(tmp, userList->current->dir);
    MovePath(dirTree, tmp);
}