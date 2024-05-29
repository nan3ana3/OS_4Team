#include "../include/main.h"

// 디렉토리 노드를 해제
void DestroyNode(DirectoryNode* dirNode)
{
    free(dirNode);
}

// 주어진 디렉토리 노드의 경로를 계산하여 파일에 기록
char* PrintDirectoryPath(DirectoryTree* dirTree)
{
    DirectoryNode* current = dirTree->current;
    char path[MAX_DIR * 2] = "/";  // 경로 저장 배열, 루트 디렉토리로 초기화
    char* segments[MAX_DIR]; //디렉토리 이름 저장 포인터
    int segmentCount = 0; //세그먼트의 수

    // 루트 디렉토리에 도달할 때까지 반복
    while (current != dirTree->root) {
        segments[segmentCount++] = current->name; //디렉토리 이름을 배열에 저장
        current = current->Parent; // 상위 디렉토리로 이동
    }

    // 경로를 역순으로 연결하여 최종 경로 구성
    for (int i = segmentCount - 1; i >= 0; --i) {
        strncat(path, segments[i], MAX_DIR * 2 - strlen(path) - 1);
        if (i > 0) { //슬래시 중복 방지
            strncat(path, "/", MAX_DIR * 2 - strlen(path) - 1);
        }
    }
    // 최종 경로 출력
    return path;
}
//getPath 대신 PrintDirectoryPath를 이용하여 writeNode 구현
char* PrintParentDirectoryPath(DirectoryTree* dirTree, DirectoryNode* dirNode) {
    if (dirNode->Parent == dirTree->root) {
        // 주어진 노드의 부모노드가 루트 노드인 경우 (/), 루트 노드 경로를 반환
        char* rootPath = (char*)malloc(2);  // '/'와 null 문자 공간
        if (rootPath != NULL) {
            strcpy(rootPath, "/");
        }
        return rootPath;
    }
    else {
        return PrintParentDirectoryPath(dirTree, dirNode->Parent);
    }
}


// 디렉토리 노드를 파일에 기록
void WriteNode(DirectoryTree* dirTree, DirectoryNode* dirNode) {
    fprintf(Directory, "%s %c %d ", dirNode->name, dirNode->type, dirNode->mode);
    fprintf(Directory, "%d %d %d %d %d %d %d ", dirNode->SIZE, dirNode->UserID, dirNode->GroupID, dirNode->month, dirNode->day, dirNode->hour, dirNode->minute);

    if (dirNode == dirTree->root) //주어진 노드가 루트 노드일 경우
        fprintf(Directory, "\n");
    // 부모 노드의 경로 출력
    else {
        char* Parentpath = PrintParentDirectoryPath(dirTree, dirNode);
        if (Parentpath != NULL) {
            fprintf(Directory, "%s\n", Parentpath);
            free(Parentpath);  // 경로 문자열 메모리 해제
        }
    }
    if (dirNode->RightSibling != NULL) {
        WriteNode(dirTree, dirNode->RightSibling);
    }
    if (dirNode->LeftChild != NULL) {
        WriteNode(dirTree, dirNode->LeftChild);
    }
}
//void WriteNode(DirectoryTree* dirTree, DirectoryNode* dirNode, Stack* dirStack)
//{
//    // 노드 정보 기록: 디렉토리 노드의 이름, 타입, 모드, 크기, UID, GID, 날짜 및 시간을 파일에 기록
//    fprintf(Directory, "%s %c %d ", dirNode->name, dirNode->type, dirNode->mode);
//    fprintf(Directory, "%d %d %d %d %d %d %d", dirNode->SIZE, dirNode->UserID, dirNode->GroupID, dirNode->month, dirNode->day, dirNode->hour, dirNode->minute);
//
//    if(dirNode == dirTree->root)
//        fprintf(Directory, "\n");
//
//    // 경로 기록: 루트 노드가 아닌 경우 getPath를 호출하여 경로를 기록
//    else
//        getPath(dirTree, dirNode, dirStack);
//
//    // 형제 노드 기록: 오른쪽 형제 노드가 있으면 재귀적으로 WriteNode를 호출
//    if(dirNode->RightSibling != NULL){
//        WriteNode(dirTree, dirNode->RightSibling, dirStack);
//    }
//
//    // 자식 노드 기록: 왼쪽 자식 노드가 있으면 재귀적으로 WriteNode를 호출
//    if(dirNode->LeftChild != NULL){
//        WriteNode(dirTree, dirNode->LeftChild, dirStack);
//    }
//}

// 파일에서 디렉토리 노드를 읽어와 트리에 추가
int ReadNode(DirectoryTree* dirTree, char* tmp)
{
    // 새 노드 할당: NewNode를 할당하고 초기화
    DirectoryNode* NewNode = (DirectoryNode*)malloc(sizeof(DirectoryNode));
    DirectoryNode* tmpNode = NULL;
    char* command;

    NewNode->LeftChild = NULL;
    NewNode->RightSibling = NULL;
    NewNode->Parent = NULL;

    // 정보 추출: strtok을 사용하여 문자열 tmp에서 정보를 추출하고 NewNode에 저장
    command = strtok(tmp, " ");
    strncpy(NewNode->name, command, MAX_NAME);
    command = strtok(NULL, " ");
    NewNode->type = command[0];
    command = strtok(NULL, " ");
    NewNode->mode = atoi(command);
    Atoi_permission(NewNode);
    command = strtok(NULL, " ");
    NewNode->SIZE = atoi(command);
    command = strtok(NULL, " ");
    NewNode->UserID = atoi(command);
    command = strtok(NULL, " ");
    NewNode->GroupID = atoi(command);
    command = strtok(NULL, " ");
    NewNode->month = atoi(command);
    command = strtok(NULL, " ");
    NewNode->day = atoi(command);
    command = strtok(NULL, " ");
    NewNode->hour = atoi(command);
    command = strtok(NULL, " ");
    NewNode->minute = atoi(command);

    command = strtok(NULL, " ");
    if(command != NULL){
        command[strlen(command)-1] = '\0';
        // 경로 이동: MovePath를 호출하여 디렉토리 트리의 현재 위치를 경로로 이동
        MovePath(dirTree, command);

        // 노드 연결: 부모 노드와 연결하고, 형제 노드로 연결합니다. 루트 노드인 경우 루트로 설정
        NewNode->Parent = dirTree->current;

        if(dirTree->current->LeftChild == NULL){
            dirTree->current->LeftChild = NewNode;
        }
        else{
            tmpNode = dirTree->current->LeftChild;

            while(tmpNode->RightSibling != NULL)
                tmpNode = tmpNode->RightSibling;

            tmpNode->RightSibling = NewNode;
        }
    }
    else{
        dirTree->root = NewNode;
        dirTree->current = dirTree->root;
    }

    return 0;
}

// 주어진 월을 문자열로 출력
void GetMonth(int month)
{
    const char* months[] = {
        "Invalid", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    if (month >= 1 && month <= 12) {
        printf("%s ", months[month]);
    }
    else {
        printf("Invalid month ");
    }
}
//void GetMonth(int month)
//{
//    switch(month){
//    case 1:
//        printf("Jan ");
//        break;
//    case 2:
//        printf("Feb ");
//        break;
//    case 3:
//        printf("Mar ");
//        break;
//    case 4:
//        printf("Apr ");
//        break;
//    case 5:
//        printf("May ");
//        break;
//    case 6:
//        printf("Jun ");
//        break;
//    case 7:
//        printf("Jul ");
//        break;
//    case 8:
//        printf("Aug ");
//        break;
//    case 9:
//        printf("Sep ");
//        break;
//    case 10:
//        printf("Oct ");
//        break;
//    case 11:
//        printf("Nov ");
//        break;
//    case 12:
//        printf("Dec ");
//        break;
//    default:
//        break;
//    }
//}

// 주어진 요일을 문자열로 출력
void GetWeek(int week) //요일 출력
{
    const char* weeks[] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };

    if (week >= 0 && week <= 6) {
        printf("%s ", weeks[week]);
    }
    else {
        printf("Invalid week ");
    }
}

//void GetWeek(int week)
//{
//    switch(week){
//    case 0:
//        printf("Sun ");
//        break;
//    case 1:
//        printf("Mon ");
//        break;
//    case 2:
//        printf("Tue ");
//        break;
//    case 3:
//        printf("Wed ");
//        break;
//    case 4:
//        printf("Thu ");
//        break;
//    case 5:
//        printf("Fri ");
//        break;
//    case 6:
//        printf("Sat ");
//        break;
//    default:
//        break;
//    }
//}

// 명령어 처리
void ExecuteCommand(DirectoryTree* dirTree, char* cmd) {
    if(strcmp(cmd, "") == 0 || cmd[0] == ' '){ // 명령어가 빈 문자열이거나 공백으로 시작하면 리턴
        return;
    }
    
    // for cat
    char* command;
    int check_correct;
    char* pid;
    char* token1;
    char* token2;
    char* next_token;
    command = strtok(cmd, " ");
    
    DirectoryTree tree;
    init_directory_tree(&tree);

    int result;

    
    // 박채린
    if(strcmp(cmd, "cat") == 0){ // cat 명령어 처리
         //command = strtok(NULL, " ");
         token1 = strtok(NULL, " ");
         token2 = strtok(NULL, " ");
         
       //  check_correct = 
         cat(&tree, token1, token2);
         
      }
        //instruction - add char* pid;
    else if(strcasecmp(cmd, "kill") == 0) {
           
            if(cmd!=NULL){
            	cmd = strtok(NULL, " ");
            	pid = strtok(NULL, " ");
            	kill_command(cmd, pid);
            }
            else {
            	printf("Error\n");
            }
    
    
    
    // 박진성
    } else if (strcasecmp(cmd, "cd") == 0) {
    	cmd = strtok(NULL," "); 
      cd(dirTree, cmd);

    } else if (strcasecmp(cmd, "find") == 0) {
    	cmd = strtok(NULL," "); 
     find(dirTree, cmd);
    
    } else if (strcasecmp(cmd, "pwd") == 0) {
      cmd = strtok(NULL, " ");
        pwd(dirTree, cmd);
        
    // 나윤주
    } else if (strcasecmp(cmd, "ls") == 0) {
        cmd = strtok(NULL, " ");
        ls(dirTree, cmd);
    } else if(strcasecmp(command, "mkdir") == 0){ // mkdir 명령어 처리
        command = strtok(NULL, " ");
        check_correct = mkdir(dirTree, command);
        if(check_correct == 0){
            SaveDir(dirTree, dStack);
        }
    }

    // 유연우    
     else if(strcasecmp(cmd, "man") == 0) {  // man 명령어 처리
            cmd = strtok(NULL, " ");
            man(cmd);
    }
    else if(strcasecmp(cmd, "clear") == 0) { // clear 명령어 처리
            clear();
    }
        
        

       else if(strcasecmp(cmd, "exit") == 0){ // exit 명령어 처리
            printf("Logout\n");
            exit(0);
    }
    else{ // 명령어가 없을 경우 처리
        printf("command not found: %s\n", cmd);
    }
}

void Start()
{
    printf("Last login: ");
    GetWeek(userList->current->wday);
    GetMonth(userList->current->month);
    printf("%d %02d:%02d:%02d %d\n", userList->current->mday, userList->current->hour, userList->current->minute, userList->current->sec, userList->current->year);
}

//void Start()
//{
//    printf("Last login: ");
//    GetWeek(userList->current->wday); // 마지막 로그인 요일 출력
//    GetMonth(userList->current->month); // 마지막 로그인 월 출력
//    printf("%d %02d:%02d:%02d %d\n", userList->current->day, userList->current->hour, userList->current->minute, userList->current->sec, userList->current->year); // 마지막 로그인 날짜와 시간 출력
//}

// 현재 사용자의 promptheader를 출력함
//프롬프트 기호 출력
//user@os-termproject:현재 디렉토리 일반사용자($)
//JS@os-termproject:~$  
void PrintPrompt(DirectoryTree* dirTree) {
    // 변수 선언
    char user;

    // 현재 사용자가 루트 사용자(헤드 노드)인 경우 프롬프트 기호를 '#'로, 아니면 '$'로 설정
    if (userList->current == userList->head)
        user = '#';
    else
        user = '$';

    // 사용자 이름과 호스트 이름 출력
    BOLD; GREEN;
    printf("%s@os-termproject", userList->current->name);
    DEFAULT;
    printf(":");

    // 현재 디렉토리 경로 가져오기
    char* path = PrintDirectoryPath(dirTree);

    // 홈 디렉토리 경로 가져오기
    char* homeDir = userList->current->dir;

    // 루트 사용자인 경우 또는 현재 경로가 홈 디렉토리와 다른 경우 전체 경로 출력
    if (userList->current == userList->head || strncmp(path, homeDir, strlen(homeDir)) != 0) {
        BOLD; BLUE;
        printf("%s", path);
    }
    else {
        // 현재 경로가 홈 디렉토리와 같은 경우 '~'로 표시
        BOLD; BLUE;
        printf("~%s", path + strlen(homeDir));
    }

    // 기본 스타일로 되돌리고 프롬프트 기호를 출력
    DEFAULT;
    printf("%c\n", user);
}


//void PrintHead(DirectoryTree* dirTree, Stack* dirStack)
//{
//    // 변수 선언
//    DirectoryNode* tmpNode = NULL;
//    char tmp[MAX_DIR] = "";
//    char tmp2[MAX_DIR] = "";
//    char user;
//
//    if(userList->current == userList->head)
//        user = '#'; // 루트 사용자일 경우
//    else
//        user = '$'; // 일반 사용자일 경우
//
//    BOLD;GREEN; // 글자 색상 설정
//    printf("%s@2-os-linux", userList->current->name); // 사용자 이름 출력
//    DEFAULT; // 글자 색상 초기화
//    printf(":");
//    tmpNode = dirTree->current;
//
//    if(tmpNode == dirTree->root){
//        strcpy(tmp, "/"); // 루트 노드일 경우 경로를 "/"로 설정
//    }
//    else{
//        while(tmpNode->Parent != NULL){
//            Push(dirStack, tmpNode->name); // 부모 노드가 NULL이 될 때까지 스택에 푸시
//            tmpNode = tmpNode->Parent;
//        }
//        while(IsEmpty(dirStack) == 0){
//                strcat(tmp, "/");
//                strcat(tmp ,Pop(dirStack)); // 경로 구성
//        }
//    }
//
//    strncpy(tmp2, tmp, strlen(userList->current->dir)); // 현재 경로 복사
//
//    if(userList->current == userList->head){
//        BOLD;BLUE;
//        printf("%s", tmp); // 루트 사용자인 경우 경로 출력
//    }
//    else if(strcmp(userList->current->dir, tmp2) != 0){
//        BOLD;BLUE;
//        printf("%s", tmp); // 현재 경로와 사용자 디렉토리가 다른 경우 경로 출력
//    }
//    else{
//        tmpNode = dirTree->current;
//        while(tmpNode->Parent != NULL){
//            Push(dirStack, tmpNode->name);
//            tmpNode = tmpNode->Parent;
//        }
//        Pop(dirStack);
//        Pop(dirStack);
//        BOLD;BLUE;
//        printf("~"); // 현재 경로가 사용자 디렉토리와 같은 경우 "~"로 출력
//        while(IsEmpty(dirStack) == 0){
//            printf("/");
//            printf("%s",Pop(dirStack));
//        }
//    }
//    DEFAULT; // 글자 색상 초기화
//    printf("%c ", user); // 사용자 프롬프트 출력
//}