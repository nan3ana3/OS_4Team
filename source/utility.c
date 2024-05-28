#include "../include/main.h"


// 명령어 처리
void ExecuteCommand(DirectoryTree* dirTree, char* cmd) {
    if (cmd == NULL || *cmd == '\0' || *cmd == ' ') {
        return;
    }
    char* command;
    int check_correct;
    char* pid;
    char* token1;
    char* token2;
    char* next_token;
    
    char* token = strtok(cmd, " ");
    char* argument = strtok(NULL, " ");
    int result;
    
    DirectoryTree tree;
    // init_directory_tree(&tree);
    
     if(strcmp(cmd, "cat") == 0){ // cat 명령어 처리
         //command = strtok(NULL, " ");
         token1 = strtok(NULL, " ");
         token2 = strtok(NULL, " ");
         
       //  check_correct =
         // cat(&tree, token1, token2);
         
      }
    else if (strcasecmp(token, "cd") == 0) {
        cd(dirTree, argument);
    } else if (strcasecmp(token, "find") == 0) {
        find(dirTree, argument);
    } else if (strcasecmp(token, "ls") == 0) {
        ls(dirTree, argument);
    } else if (strcasecmp(token, "mkdir") == 0) {
        result = mkdir(dirTree, argument);
        if (result == 0) {
            SaveDir(dirTree);
        }
    } else if (strcasecmp(token, "pwd") == 0) {
        pwd(dirTree, argument);
    } else if (strcasecmp(token, "rm") == 0) {
        rm(dirTree, token, argument);
    } else if (strcasecmp(token, "man") == 0) {
        man(argument);
    } else if (strcasecmp(token, "clear") == 0) {
        clear();
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
    }   
    else if (strcasecmp(token, "exit") == 0) {
        printf("Logout\n");
        exit(0);
    } else {
        printf("command not found: %s\n", token);
    }
}


//프롬프트 기호 출력
//user@os-termproject:현재 디렉토리 일반사용자($)
//JS@os-termproject:~$  
// 현재 사용자의 promptheader를 출력함
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


// 족보 그대로 사용
void DestroyNode(DirectoryNode* dirNode)
{
    free(dirNode);
}

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



void Start()
{
    printf("Last login: ");
    GetWeek(userList->current->wday);
    GetMonth(userList->current->month);
    printf("%d %02d:%02d:%02d %d\n", userList->current->mday, userList->current->hour, userList->current->minute, userList->current->sec, userList->current->year);
}

//pwd.h
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

int ReadNode(DirectoryTree* dirTree, char* tmp) //그대로 사용
{
    DirectoryNode* NewNode = (DirectoryNode*)malloc(sizeof(DirectoryNode));
    DirectoryNode* tmpNode = NULL;
    char* command;

    NewNode->LeftChild = NULL;
    NewNode->RightSibling = NULL;
    NewNode->Parent = NULL;

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
    if (command != NULL) {
        command[strlen(command) - 1] = '\0';
        ChangeDirectory(dirTree, command);
        NewNode->Parent = dirTree->current;

        if (dirTree->current->LeftChild == NULL) {
            dirTree->current->LeftChild = NewNode;
        }
        else {
            tmpNode = dirTree->current->LeftChild;

            while (tmpNode->RightSibling != NULL)
                tmpNode = tmpNode->RightSibling;

            tmpNode->RightSibling = NewNode;
        }
    }
    else {
        dirTree->root = NewNode;
        dirTree->current = dirTree->root;
    }

    return 0;
}

