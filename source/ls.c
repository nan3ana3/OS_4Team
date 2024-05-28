#include "../include/main.h"

int ls_cnt = 1;

// 도움말 출력 함수
void display_help() {
    printf("Usage: ls [OPTION]... [FILE]...\n");
    printf("List information about the FILEs (the current directory by default).\n");
    printf("Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.\n\n");
    printf("Mandatory arguments to long options are mandatory for short options too.\n");
    printf("  -a, --all\t do not ignore entries starting with .\n");
    printf("  -l       \t use a long listing format\n");
    printf("  -al, -la \t use a long listing format and do not ignore entries starting with .\n");
    printf("      --help\t display this help and exit\n\n");
    printf("Exit status:\n");
    printf(" 0 if OK,\n");
    printf(" 1 if minor problems (e.g., cannot access subdirectory),\n");
    printf(" 2 if serious trouble (e.g., cannot access command-line argument).\n\n");
    printf("GNU coreutils online help: <https://www.gnu.org/software/coreutils/>\n");
    printf("Report any translation bugs to <https://translationproject.org/team/>\n");
    printf("Full documentation <https://www.gnu.org/software/coreutils/ls>\n");
    printf("or available locally via: info '(coreutils) ls invocation'\n");
}

// ls 명령어 스레드 함수
void* ls_thread(void* arg) {
    ThreadTree* threadData = (ThreadTree*)arg;
    DirectoryTree* dirTree = threadData->threadTree;
    char* path = threadData->command;
    int option = threadData->option;
    DirectoryNode* currentNode = dirTree->current;

    if (ls_cnt > 1) {
        printf("%s:\n", path);
    }

    if (MovePath(dirTree, path) != 0) {
        printf("ls: '%s': No such file or directory.\n", path);
    } else {
        ListDir(dirTree, option);
        dirTree->current = currentNode;
    }

    pthread_exit(NULL);
}

// ls 명령어 처리 함수
int ls(DirectoryTree* dirTree, char* command) {
    if (!command) {
        ListDir(dirTree, 0);
        return 0;
    }

    pthread_t threadArr[MAX_THREAD];
    ThreadTree threadTree[MAX_THREAD];
    char* cmd;
    int option = 0;
    int thread_cnt = 0;

    if (command[0] == '-') {
        if (strcmp(command, "-l") == 0) {
            option = 2;
        } else if (strcmp(command, "-a") == 0) {
            option = 1;
        } else if (strcmp(command, "-al") == 0 || strcmp(command, "-la") == 0) {
            option = 3;
        } else if (strcmp(command, "--help") == 0) {
            display_help();
            return 0;
        } else {
            printf("ls: invalid option -- '%s'\n", command + 1);
            printf("Try 'ls --help' for more information.\n");
            return -1;
        }
        cmd = strtok(NULL, " ");
        if (!cmd) {
            ListDir(dirTree, option);
            return 0;
        }
    } else {
        cmd = command;
    }

    while (cmd) {
        threadTree[thread_cnt].threadTree = dirTree;
        threadTree[thread_cnt].option = option;
        threadTree[thread_cnt++].command = cmd;
        cmd = strtok(NULL, " ");
        ls_cnt++;
    }

    for (int i = 0; i < thread_cnt; i++) {
        pthread_create(&threadArr[i], NULL, ls_thread, (void*)&threadTree[i]);
        pthread_join(threadArr[i], NULL);
    }

    ls_cnt = 1;
    return 0;
}

// 디렉토리 내용 목록 출력 함수
int ListDir(DirectoryTree* dirTree, int option) {
    DirectoryNode* tmpNode = dirTree->current->LeftChild;
    if (!tmpNode) return -1;

    if (HasPermission(dirTree->current, 'r') != 0) {
        printf("ls: '%s': Permission denied\n", dirTree->current->name);
        return -1;
    }

    if (option == 0 || option == 1) {
        if (option == 1) {
            BOLD; BLUE;
            printf(".       ");
            DEFAULT;
            if (dirTree->current != dirTree->root) {
                BOLD; BLUE;
                printf("..      ");
                DEFAULT;
            }
        }
        while (tmpNode) {
            if (option == 0 && strncmp(tmpNode->name, ".", 1) == 0) {
                tmpNode = tmpNode->RightSibling;
                continue;
            }
            if (tmpNode->type == 'd') {
                BOLD; BLUE;
                printf("%s      ", tmpNode->name);
                DEFAULT;
            } else {
                printf("%s      ", tmpNode->name);
            }
            tmpNode = tmpNode->RightSibling;
        }
        printf("\n");
    } else {
        DirectoryNode* tmpNode2 = NULL;
        int total = 0;
        if (option == 3) {
            tmpNode2 = dirTree->current->LeftChild;
            while (tmpNode2) {
                if (tmpNode2->type == 'd') total++;
                tmpNode2 = tmpNode2->RightSibling;
            }
            PrintLongFormat(dirTree->current, ".", total);
            if (dirTree->current != dirTree->root) {
                tmpNode2 = dirTree->current->Parent->LeftChild;
                total = 0;
                while (tmpNode2) {
                    if (tmpNode2->type == 'd') total++;
                    tmpNode2 = tmpNode2->RightSibling;
                }
                PrintLongFormat(dirTree->current->Parent, "..", total);
            }
        }
        while (tmpNode) {
            if (option == 2 && strncmp(tmpNode->name, ".", 1) == 0) {
                tmpNode = tmpNode->RightSibling;
                continue;
            }
            tmpNode2 = tmpNode->LeftChild;
            total = 1;
            while (tmpNode2) {
                if (tmpNode2->type == 'd') total++;
                tmpNode2 = tmpNode2->RightSibling;
            }
            PrintLongFormat(tmpNode, tmpNode->name, total);
            tmpNode = tmpNode->RightSibling;
        }
    }
    return 0;
}

// 긴 형식으로 파일 정보를 출력하는 함수
void PrintLongFormat(DirectoryNode* node, char* name, int total) {
    printf("%c", node->type);
    PrintPermission(node);
    printf("%3d ", total);
    printf("%-9s %-9s ", FindUID(node), FindGID(node));
    printf("%5d ", node->SIZE);
    GetMonth(node->month);
    printf(" %2d %02d:%02d ", node->day, node->hour, node->minute);
    if (node->type == 'd') {
        BOLD; BLUE;
        printf("%s\n", name);
        DEFAULT;
    } else {
        printf("%s\n", name);
    }
}

//#include "../include/main.h"
//int ls_cnt = 1;
//int ls(DirectoryTree* dirTree, char* command)
//{
//    DirectoryNode* tmpNode = NULL;
//    pthread_t threadArr[MAX_THREAD];
//    ThreadTree threadTree[MAX_THREAD];
//    char* cmd;
//    int option = 0;
//    int thread_cnt = 0;
//
//    if (command == NULL) {
//        ListDir(dirTree, 0);
//        return 0;
//    }
//    if (command[0] == '-') {    //옵션이 있을 경우
//        if (strcmp(command, "-l") == 0) {      //옵션이 -l일 경우
//            option = 2;
//            cmd = strtok(NULL, " ");
//            if (cmd == NULL) {
//                ListDir(dirTree, 2);
//            }
//        }
//        else if (strcmp(command, "-a") == 0) {      //옵션이 -a일 경우
//            option = 1;
//            cmd = strtok(NULL, " ");
//            if (cmd == NULL) {
//                ListDir(dirTree, 1);
//            }
//        }
//        else if (strcmp(command, "-al") == 0 || strcmp(command, "-la") == 0) {       //옵션이 -al, -la일 경우
//            option = 3;
//            cmd = strtok(NULL, " ");
//            if (cmd == NULL) {
//                ListDir(dirTree, 3);
//            }
//        }
//        else if (strcmp(command, "--help") == 0) {
//            printf("Usage: ls [OPTION]... [FILE]...\n");
//            printf("List information about the FILEs (the current directory by default).\n");
//            printf("Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.\n\n");
//            
//            printf("Mandatory arguments to long [+options are mandatory for short options too.\n");
//            printf("  -a, --all\t do not ignore entries starting with .\n");
//            printf("  -l       \t use a long listing format\n");
//            printf("      --help\t display this help and exit\n\n");
//            
//            printf("The SIZE argument is an integer and optional unit (example: 10K is 10*1024).\n");
//            printf("Units are K,M,G,T,P,E,Z,Y (powers of 1024) or KB,MB,... (powers of 1000).\n");
//            printf("Binary prefixes can be used, too: Kib=K, MiB=M, and so on.\n\n");
//            
//            printf("The TIME_STYLE argument can be full-iso, long-isp, iso, locale, or +FORMAT.\n");
//            printf("FORMAT is interpreted like in date(1). If FORMAT is FORMAT1<newline>FORMAT2,\n");
//            printf("then FORMAT1 applies to non-recent files and FORNAT2 to recent files.\n");
//            printf("TIME_STYLE prefixed with 'posix-' takes effect only outside the POSIX locale.\n");
//            printf("Also the TIME_STYLE environment variable sets the default style to use.\n\n");
//            
//            printf("Using color to distinguish file types is diasbled both by default and\n");
//            printf("with --color=never. With --color=autp, ls emits color codes only when\n");
//            printf("standard output is connected to a terminal. The LS_COLORS environmnet\n");
//            printf("variable can change the settings. User the dircolors command to set it\n\n");
//            
//            printf("Exit status:\n");
//            printf(" 0 if OK,\n");
//            printf(" 1 if minor problems (e.g., cannot access subdirectory),\n");
//            printf(" 2 if serious trouble (e.g., cannot access command-line argument).\n\n");
//            
//            printf("GNU coreutils online help: <https://www.gnu.org/software/coreutils/>\n");
//            printf("Report any translation bugs to <https://translationproject.org/team/>\n");
//            printf("Full documentation <https://www.gnu.org/software/coreutils/mkdir>\n");
//            printf("or available locally via: info '(coreutils) mkdir invocation'\n");
//            return -1;
//        }
//        else {      //다른 옵션일 경우 에러
//            cmd = strtok(command, "-");
//            printf("ls: invalid option -- '%s'\n", cmd);
//            printf("Try 'ls --help' for more information.\n");
//            return -1;
//        }
//    }
//    else {
//        cmd = strtok(NULL, " ");
//        threadTree[thread_cnt].threadTree = dirTree;
//        threadTree[thread_cnt].option = option;
//        threadTree[thread_cnt++].command = command;
//    }
//    while(cmd != NULL){
//        threadTree[thread_cnt].threadTree = dirTree;
//        threadTree[thread_cnt].option = option;
//        threadTree[thread_cnt++].command = cmd;
//        cmd = strtok(NULL, " ");
//        ls_cnt++;
//    }
//    for (int i = 0; i < thread_cnt; i++) {
//        pthread_create(&threadArr[i], NULL, ls_thread, (void *)&threadTree[i]);
//        pthread_join(threadArr[i], NULL);
//    }
//    ls_cnt = 1;
//    return 0;
//}
//
//void* ls_thread(void *arg) {
//    ThreadTree *threadTree = (ThreadTree *)arg;
//    DirectoryTree *dirTree = threadTree->threadTree;
//    char *command = threadTree->command;
//    DirectoryNode *tmpNode = NULL;
//    int option = threadTree->option;
//    int check_exist;
//
//    tmpNode = dirTree->current;
//    if (ls_cnt > 1)
//        printf("%s:\n", command);
//    check_exist = MovePath(dirTree, command);
//    if (check_exist)
//    {
//        printf("ls: '%s': No such file or direcory.\n", command);
//        return -1;
//    }
//    ListDir(dirTree, option);
//    dirTree->current = tmpNode;
//    pthread_exit(NULL);     //스레드 실행 끝
//}
//
//int ListDir(DirectoryTree* dirTree, int option)
//{
//    //variables
//    DirectoryNode* tmpNode = NULL;
//    DirectoryNode* tmpNode2 = NULL;
//    char type;
//    int ls_cnt;
//
//    tmpNode = dirTree->current->LeftChild;
//
//    if (HasPermission(dirTree->current, 'r') != 0) {
//        printf("ls: '%s: Permission denied", dirTree->current->name);
//        return -1;
//    }
//    if (option == 0 || option == 1) {
//        if (option == 0) {
//            if (tmpNode == NULL)
//                return -1;
//        }
//        if (option == 1) {
//            BOLD; BLUE;
//            printf(".       ");
//            DEFAULT;
//            if (dirTree->current != dirTree->root) {
//                BOLD; BLUE;
//                printf("..      ");
//                DEFAULT;
//            }
//        }
//        while (tmpNode != NULL) {
//            if (option == 0) {
//                if (strncmp(tmpNode->name, ".", 1) == 0) {
//                    tmpNode = tmpNode->RightSibling;
//                    continue;
//                }
//            }
//            if (tmpNode->type == 'd') {
//                BOLD; BLUE;
//                printf("%s      ", tmpNode->name);
//                DEFAULT;
//            }
//            else
//                printf("%s      ", tmpNode->name);
//            tmpNode = tmpNode->RightSibling;
//        }
//        if (ls_cnt > 1)
//            printf("\n");
//    }
//    else {
//        if (option == 2) {
//            if (tmpNode == NULL) {
//                printf("total: 0\n");
//                return -1;
//            }
//        }
//        if (option == 3) {
//            tmpNode2 = dirTree->current->LeftChild;
//            if (tmpNode2 == NULL) {
//                ls_cnt = 2;
//            }
//            else {
//                if (tmpNode2->type == 'd')
//                    ls_cnt = 3;
//                else
//                    ls_cnt = 2;
//
//                while (tmpNode2->RightSibling != NULL) {
//                    tmpNode2 = tmpNode2->RightSibling;
//                    if (tmpNode2->type == 'd')
//                        ls_cnt = ls_cnt + 1;
//                }
//            }
//
//            printf("%c", dirTree->current->type);
//            PrintPermission(dirTree->current);
//            printf("%3d", ls_cnt);
//            printf("   ");
//            printf("%-5s%-5s", GetUID(dirTree->current), GetGID(dirTree->current));
//            printf("%5d ", dirTree->current->SIZE);
//            GetMonth(dirTree->current->month);
//            printf(" %2d %02d:%02d ", dirTree->current->day, dirTree->current->hour, dirTree->current->minute);
//            BOLD; BLUE;
//            printf(".\n");
//            DEFAULT;
//
//            if (dirTree->current != dirTree->root) {
//                tmpNode2 = dirTree->current->Parent->LeftChild;
//                if (tmpNode2 == NULL)
//                    ls_cnt = 2;
//                else {
//                    if (tmpNode2->type == 'd')
//                        ls_cnt = 3;
//                    else
//                        ls_cnt = 2;
//
//                    while (tmpNode2->RightSibling != NULL) {
//                        tmpNode2 = tmpNode2->RightSibling;
//                        if (tmpNode2->type == 'd')
//                            ls_cnt = ls_cnt + 1;
//                    }
//                }
//                printf("%c", dirTree->current->Parent->type);
//               PrintPermission(dirTree->current->Parent);
//                printf("%3d", ls_cnt);
//                printf("   ");
//                printf("%-5s%-5s", GetUID(dirTree->current->Parent), GetGID(dirTree->current->Parent));
//                printf("%5d ", dirTree->current->SIZE);
//                GetMonth(dirTree->current->Parent->month);
//                printf(" %2d %02d:%02d ", dirTree->current->Parent->day, dirTree->current->Parent->hour, dirTree->current->Parent->minute);
//                BOLD; BLUE;
//                printf("..\n");
//                DEFAULT;
//            }
//        }
//        while (tmpNode != NULL) {
//            if (option == 2) {
//                if (strncmp(tmpNode->name, ".", 1) == 0) {
//                    tmpNode = tmpNode->RightSibling;
//                    continue;
//                }
//            }
//            tmpNode2 = tmpNode->LeftChild;
//            if (tmpNode2 == NULL) {
//                if (tmpNode->type == 'd')
//                    ls_cnt = 2;
//                else
//                    ls_cnt = 1;
//            }
//            else {
//                if (tmpNode2->type == 'd')
//                    ls_cnt = 3;
//                else
//                    ls_cnt = 2;
//
//                while (tmpNode2->RightSibling != NULL) {
//                    tmpNode2 = tmpNode2->RightSibling;
//                    if (tmpNode2->type == 'd')
//                        ls_cnt = ls_cnt + 1;
//                }
//            }
//            if (tmpNode->type == 'd')
//                type = 'd';
//            else if (tmpNode->type == 'f')
//                type = '-';
//            printf("%c", type);
//            PrintPermission(tmpNode);
//            printf("%3d", ls_cnt);
//            printf("   ");
//            printf("%-9s%-9s", GetUID(tmpNode), GetGID(tmpNode));
//            printf("%5d ", tmpNode->SIZE);
//            GetMonth(tmpNode->month);
//            printf(" %2d %02d:%02d ", tmpNode->day, tmpNode->hour, tmpNode->minute);
//
//            if (tmpNode->type == 'd') {
//                BOLD; BLUE;
//                printf("%-15s\n", tmpNode->name);
//                DEFAULT;
//            }
//            else
//                printf("%-15s\n", tmpNode->name);
//            tmpNode = tmpNode->RightSibling;
//        }
//    }
//    return 0;
//}
