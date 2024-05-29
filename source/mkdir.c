#include "../include/main.h"

int mkdir_command(DirectoryTree* dirTree, char* command)
{
    DirectoryNode* tmpNode = NULL;
    pthread_t threadArr[MAX_THREAD];
    ThreadTree threadTree[MAX_THREAD];
    char* cmd;
    char tmp[MAX_DIR];
    char tmp2[MAX_DIR];
    char tmp3[MAX_DIR];
    int thread_cnt = 0;
    int option = 0;
    int tmpMode;

    tmpNode = dirTree->current;
    if (command == NULL) {
          printf("mkdir: missing operand\n");
          printf("Try 'mkdir --help' for more information.\n");
          return -1;
    }
    else if (command[0] == '-') { // 옵션 있을 경우
        if (strcmp(command, "-p") == 0) {
            cmd = strtok(NULL, " ");
            if (cmd == NULL) {
                printf("mkdir: missing operand\n");
                printf("Try 'mkdir --help' for more information.\n");
                return -1;
            }
            option = 1;
        }
        else if (strcmp(command, "--help") == 0) {
            printf("Usage: mkdir [OPTION]... DIRECTORY...\n");
            printf("Create the DIRECTORY(ies), if they do not already exists.\n\n");

            printf("Mandatory arguments to long options are mandatory for short options too.\n");
            printf("    -m, --mode=MODE\t set file mode (as in chmod)\n");
            printf("    -p, --parents  \t no error if existing, make parent directories as needed\n");
            printf("        --help\t display this help and exit\n\n");

            printf("GNU coreutils online help: <https://www.gnu.org/software/coreutils/>\n");
            printf("Report any translation bugs to <https://translationproject.org/team/>\n");
            printf("Full documentation <https://www.gnu.org/software/coreutils/mkdir>\n");
            printf("or available locally via: info '(coreutils) mkdir invocation'\n");
            return -1;
        }
        else {
            printf("mkdir: invalid option '%s'\n", command);
            printf("Try 'mkdir --help' for more information.\n");
            return -1;
        }
    }
    else { // 옵션 없을 경우
        cmd = strtok(NULL, " ");
        threadTree[thread_cnt].threadTree = dirTree;
        threadTree[thread_cnt].option = option;
        threadTree[thread_cnt++].command = command;
    }
    while (cmd != NULL) {
        threadTree[thread_cnt].threadTree = dirTree;
        threadTree[thread_cnt].option = option;
        threadTree[thread_cnt++].command = cmd;
        cmd = strtok(NULL, " ");
    }
    for (int i = 0; i < thread_cnt; i++) {
        pthread_create(&threadArr[i], NULL, mkdir_thread, (void*)&threadTree[i]);
        pthread_join(threadArr[i], NULL);
    }
    return 0;
}

int MakeDir(DirectoryTree* dirTree, char* cmd, char type)
{
    DirectoryNode* newNode = (DirectoryNode*)malloc(sizeof(DirectoryNode));
    DirectoryNode* tmpNode = NULL;

    if (HasPermission(dirTree->current, 'w') != 0) {
        printf("mkdir: %s: Permission denied\n", cmd);
        free(newNode);
        return -1;
    }
    if (strcmp(cmd, ".") == 0 || strcmp(cmd, "..") == 0) {
        printf("mkdir: cannot create directory '%s': File exists\n", cmd);
        free(newNode);
        return -1;
    }
    tmpNode = FindDirectoryNode(dirTree, cmd, type);
    if (tmpNode != NULL && tmpNode->type == 'd') {
        printf("mkdir: cannot create directory '%s': File exists\n", cmd);
        free(newNode);
        return -1;
    }
    time(&ltime);
    today = localtime(&ltime);

    newNode->LeftChild = NULL;
    newNode->RightSibling = NULL;

    strncpy(newNode->name, cmd, MAX_NAME);
    if (cmd[0] == '.') {
        newNode->type = 'd';
        newNode->mode = 700;
        newNode->SIZE = 4096;
    }
    else if (type == 'd') {
        newNode->type = 'd';
        newNode->mode = 755;
        newNode->SIZE = 4096;
    }
    else {
        newNode->type = 'f';
        newNode->mode = 644;
        newNode->SIZE = 0;
    }
    Atoi_permission(newNode);
    newNode->UserID = userList->current->UserID;
    newNode->GroupID = userList->current->GroupID;
    newNode->month = today->tm_mon + 1;
    newNode->day = today->tm_mday;
    newNode->hour = today->tm_hour;
    newNode->minute = today->tm_min;
    newNode->Parent = dirTree->current;

    if (dirTree->current->LeftChild == NULL) {
        dirTree->current->LeftChild = newNode;
    }
    else {
        tmpNode = dirTree->current->LeftChild;

        while (tmpNode->RightSibling != NULL) {
            tmpNode = tmpNode->RightSibling;
        }
        tmpNode->RightSibling = newNode;
    }

    return 0;
}

void* mkdir_thread(void* arg) {
    ThreadTree* threadTree = ((ThreadTree*)arg);
    DirectoryTree* dirTree = threadTree->threadTree;
    char* cmd = threadTree->command;

    DirectoryNode* tmpNode = dirTree->current;
    char tmp[MAX_DIR];
    char str[MAX_DIR];
    char tmpstr[MAX_DIR];
    char name[MAX_DIR];
    int nameLength = 0;
    int check_exist;

    strncpy(tmp, cmd, MAX_DIR);

    if (strstr(cmd, "/") == NULL) {
        MakeDir(dirTree, cmd, 'd');
    }
    else if (threadTree->option == 1) {
        int tmplen = strlen(tmp), i = 0;
        if (tmp[0] == '/') {
            dirTree->current = dirTree->root;
            i = 1;
        }
        if (tmp[tmplen - 1] == '/') {
            tmplen -= 1;
        }
        for (; i < tmplen; i++) {
            str[i] = tmp[i];
            str[i + 1] = 0;
            name[nameLength++] = tmp[i];
            if (tmp[i] == '/') {
                name[--nameLength] = 0;
                strncpy(tmpstr, str, i - 1);
                check_exist = Movecurrent(dirTree, name);
                if (check_exist == -1) {
                    MakeDir(dirTree, name, 'd');
                    check_exist = Movecurrent(dirTree, name);
                }
                nameLength = 0;
            }
        }
        name[nameLength] = 0;
        MakeDir(dirTree, name, 'd');
        dirTree->current = tmpNode;
    }
    else {
        char* p_get_directory = getDirectory(cmd);
        check_exist = MovePath(dirTree, p_get_directory);
        if (check_exist != 0) {
            printf("mkdir: '%s': No such file or directory.\n", p_get_directory);
        }
        else {
            char* cmd = strtok(tmp, "/");
            char* p_directory_name;
            while (cmd != NULL) {
                p_directory_name = cmd;
                cmd = strtok(NULL, "/");
            }
            MakeDir(dirTree, p_directory_name, 'd');
            dirTree->current = tmpNode;
        }
    }
    pthread_exit(NULL);
}

int MovePath(DirectoryTree* dirTree, char* dirPath)     //경로 이동 함수
{
    //variables
    DirectoryNode* tmpNode = NULL;
    char tmpPath[MAX_DIR];
    char* command = NULL;
    int check_exist = 0;

    //set tmp
    strncpy(tmpPath, dirPath, MAX_DIR);
    tmpNode = dirTree->current;
    if(strcmp(dirPath, "/") == 0){      // 최상위 디렉토리일 경우
        dirTree->current = dirTree->root;
    }
    else{
        if(strncmp(dirPath, "/",1) == 0){
            if(strtok(dirPath, "/") == NULL){
                return -1;
            }
            dirTree->current = dirTree->root;
        }
        command = strtok(tmpPath, "/");
        while(command != NULL){
            check_exist = Movecurrent(dirTree, command);
            if(check_exist != 0){   //경로가 없을 경우
                dirTree->current = tmpNode;
                return -1;
            }
            command = strtok( NULL, "/");
        }
    }
    return 0;
}
int Movecurrent(DirectoryTree* dirTree, char* dirPath)      //파일이 있는 디렉토리로 이동
{
    DirectoryNode* tmpNode = NULL;

    if(strcmp(dirPath,".") == 0){
    }
    else if(strcmp(dirPath,"..") == 0){
        if(dirTree->current != dirTree->root){
            dirTree->current = dirTree->current->Parent;
        }
    }
    else{
        tmpNode = FindDirectoryNode(dirTree, dirPath, 'd');
        if(tmpNode != NULL){
            dirTree->current = tmpNode;
        }
        else
            return -1;
    }
    return 0;
}