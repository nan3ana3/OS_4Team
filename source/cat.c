#include "../include/main.h"

//void init_directory_tree(DirectoryTree* tree) {
//    tree->root = (DirectoryNode*)malloc(sizeof(DirectoryNode));
//    strcpy_s(tree->root->name, MAX_NAME, "/");
//    tree->root->type = 'd';
//    tree->root->Parent = NULL;
//    tree->root->LeftChild = NULL;
//    tree->root->RightSibling = NULL;
//    tree->current = tree->root;
//}

//void cat(DirectoryTree* tree, const char* cmd) {
//    char input[100];
//    char* tokens[5];
//    int token_count = 0;
//    char* next_token;
//    char word;
//    int index = 0;
//
//    strcpy_s(input, sizeof(input), cmd);
//
//    size_t len = strlen(input);
//    if (len > 0 && input[len - 1] == '\n') {
//        input[len - 1] = '\0';
//    }
//
//    char* token = strtok_s(input, " ", &next_token);
//    while (token != NULL && token_count < 5) {
//        tokens[token_count++] = token;
//        token = strtok_s(NULL, " ", &next_token);
//    }
//
//    if (strcmp(tokens[1], ">") == 0) {
//        if (tokens[2] == NULL) {
//            printf("Error: 파일 이름을 입력하세요\n");
//            return;
//        }
//        else {
//            char filePath[200];
//            snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[2]);
//
//            FILE* newfile;
//            errno_t err = fopen_s(&newfile, filePath, "wt");
//            if (err != 0 || newfile == NULL) {
//                printf("Error: 파일 생성에 실패했습니다. Path: %s\n", filePath);
//                return;
//            }
//            else {
//                printf("입력하세요 (종료: Ctrl+D)\n");
//                while ((word = getchar()) != EOF) {
//                    fputc(word, newfile);
//                }
//                fclose(newfile);
//            }
//        }
//    }
//
//    else if (strcmp(tokens[1], "-n") == 0) {
//        if (tokens[2] == NULL) {
//            printf("Error: 파일 이름을 입력하세요\n");
//            return;
//        }
//        char filePath[200];
//        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[2]);
//        FILE* file_print;
//        errno_t err = fopen_s(&file_print, filePath, "r");
//        if (err != 0 || file_print == NULL) {
//            printf("Error: 파일 열기에 실패했습니다. Path: %s\n", filePath);
//            return;
//        }
//        int line_number = 1;
//        while (fgets(input, sizeof(input), file_print)) {
//            printf("%d  %s", line_number++, input);
//        }
//        fclose(file_print);
//    }
//
//    else if (strlen(tokens[1]) > 0) {
//        char filePath[200];
//        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[1]);
//        FILE* file_print;
//        errno_t err = fopen_s(&file_print, filePath, "r");
//        if (err != 0 || file_print == NULL) {
//            printf("Error: 파일 열기에 실패했습니다. Path: %s\n", filePath);
//            return;
//        }
//        while (fgets(input, sizeof(input), file_print)) {
//            printf("%s", input);
//        }
//        fclose(file_print);
//    }
//    else {
//        printf("Error: 다른 명령어를 시도해보세요!\n");
//    }
//}


//윤주가 고친거
//void init_directory_tree(DirectoryTree* tree) {
//    tree->root = (DirectoryNode*)malloc(sizeof(DirectoryNode));
//    strcpy(tree->root->name, "/");  // strcpy_s -> strcpy
//    tree->root->type = 'd';
//    tree->root->Parent = NULL;
//    tree->root->LeftChild = NULL;
//    tree->root->RightSibling = NULL;
//    tree->current = tree->root;
//}
//
//void cat(DirectoryTree* tree, const char* cmd) {
//    char input[100];
//    char* tokens[5] = { NULL };
//    int token_count = 0;
//    char* next_token;
//    char word;
//
//    strcpy(input, cmd);
//
//    size_t len = strlen(input);
//    if (len > 0 && input[len - 1] == '\n') {
//        input[len - 1] = '\0';
//    }
//
//    char* token = strtok_r(input, " ", &next_token);
//    while (token != NULL && token_count < 5) {
//        tokens[token_count++] = token;
//        token = strtok_r(NULL, " ", &next_token);
//    }
//
//    // Check if we have enough tokens before accessing them
//    if (token_count < 2) {
//        printf("Error: 명령어를 확인하세요\n");
//        return;
//    }
//
//    if (strcmp(tokens[1], ">") == 0) {
//        if (token_count < 3 || tokens[2] == NULL) {
//            printf("Error: 파일 이름을 입력하세요\n");
//            return;
//        }
//        char filePath[200];
//        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[2]);
//
//        FILE* newfile = fopen(filePath, "wt");
//        if (newfile == NULL) {
//            printf("Error: 파일 생성에 실패했습니다. Path: %s\n", filePath);
//            return;
//        } else {
//            printf("입력하세요 (종료: Ctrl+D)\n");
//            while ((word = getchar()) != EOF) {
//                fputc(word, newfile);
//            }
//            fclose(newfile);
//        }
//    } else if (strcmp(tokens[1], "-n") == 0) {
//        if (token_count < 3 || tokens[2] == NULL) {
//            printf("Error: 파일 이름을 입력하세요\n");
//            return;
//        }
//        char filePath[200];
//        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[2]);
//        FILE* file_print = fopen(filePath, "r");
//        if (file_print == NULL) {
//            printf("Error: 파일 열기에 실패했습니다. Path: %s\n", filePath);
//            return;
//        }
//        int line_number = 1;
//        while (fgets(input, sizeof(input), file_print)) {
//            printf("%d  %s", line_number++, input);
//        }
//        fclose(file_print);
//    } else if (strlen(tokens[1]) > 0) {
//        char filePath[200];
//        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[1]);
//        FILE* file_print = fopen(filePath, "r");
//        if (file_print == NULL) {
//            printf("Error: 파일 열기에 실패했습니다. Path: %s\n", filePath);
//            return;
//        }
//        while (fgets(input, sizeof(input), file_print)) {
//            printf("%s", input);
//        }
//        fclose(file_print);
//    } else {
//        printf("Error: 다른 명령어를 시도해보세요!\n");
//    }
//}

// 채린님이 고친거
void init_directory_tree(DirectoryTree* tree) {
    tree->root = (DirectoryNode*)malloc(sizeof(DirectoryNode));
    strcpy(tree->root->name, "/");
    tree->root->type = 'd';
    tree->root->Parent = NULL;
    tree->root->LeftChild = NULL;
    tree->root->RightSibling = NULL;
    tree->current = tree->root;
}

void cat(DirectoryTree* tree, const char* cmd) {
    char input[100];
    char* tokens[5];
    int token_count = 0;
    char* next_token;
    char word;
    int index = 0;

    strcpy(input, cmd);

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    char* token = strtok_r(input, " ", &next_token);
    while (token != NULL && token_count < 5) {
        tokens[token_count++] = token;
        token = strtok_r(NULL, " ", &next_token);
    }

    if (strcmp(tokens[1], ">") == 0) {
        if (tokens[2] == NULL) {
            printf("Error: Please enter a file name.\n");
            return;
        }
        else {
            char filePath[200];
            snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[2]);

            FILE* newfile = fopen(filePath, "wt");
            if (newfile == NULL) {
                printf("Error: File creation failed. Path: %s\n", filePath);
                return;
            }
            else {
                printf("Please enter (Close : Ctrl+D)\n");
                while ((word = getchar()) != EOF) {
                    fputc(word, newfile);
                }
                fclose(newfile);
            }
        }
    }

    else if (strcmp(tokens[1], "-n") == 0) {
        if (tokens[2] == NULL) {
            printf("Error: 파일 이름을 입력하세요\n");
            return;
        }
        char filePath[200];
        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[2]);
        FILE* file_print = fopen(filePath, "r");
        if (file_print == NULL) {
            printf("Error: Filed to open file. Path: %s\n", filePath);
            return;
        }
        int line_number = 1;
        while (fgets(input, sizeof(input), file_print)) {
            printf("%d  %s", line_number++, input);
        }
        fclose(file_print);
    }

    else if (strlen(tokens[1]) > 0) {
        char filePath[200];
        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[1]);
        FILE* file_print = fopen(filePath, "r");
        if (file_print == NULL) {
            printf("Error: Failed to open file. Path: %s\n", filePath);
            return;
        }
        while (fgets(input, sizeof(input), file_print)) {
            printf("%s", input);
        }
        fclose(file_print);
    }
    else {
        printf("Error: Try another command!\n");
    }
}

