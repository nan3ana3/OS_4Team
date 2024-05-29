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
//            printf("Error: ¨¡AAI AI?¡×A¡í AO¡¤ACI¨«¨«¢¯a\n");
//            return;
//        }
//        else {
//            char filePath[200];
//            snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[2]);
//
//            FILE* newfile;
//            errno_t err = fopen_s(&newfile, filePath, "wt");
//            if (err != 0 || newfile == NULL) {
//                printf("Error: ¨¡AAI ¡íy¨«¨¬¢¯¢® ©«C¨¡¨¢C©¬©«A?I?U. Path: %s\n", filePath);
//                return;
//            }
//            else {
//                printf("AO¡¤ACI¨«¨«¢¯a (A?¡¤a: Ctrl+D)\n");
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
//            printf("Error: ¨¡AAI AI?¡×A¡í AO¡¤ACI¨«¨«¢¯a\n");
//            return;
//        }
//        char filePath[200];
//        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[2]);
//        FILE* file_print;
//        errno_t err = fopen_s(&file_print, filePath, "r");
//        if (err != 0 || file_print == NULL) {
//            printf("Error: ¨¡AAI ¢¯¡©¡¾a¢¯¢® ©«C¨¡¨¢C©¬©«A?I?U. Path: %s\n", filePath);
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
//            printf("Error: ¨¡AAI ¢¯¡©¡¾a¢¯¢® ©«C¨¡¨¢C©¬©«A?I?U. Path: %s\n", filePath);
//            return;
//        }
//        while (fgets(input, sizeof(input), file_print)) {
//            printf("%s", input);
//        }
//        fclose(file_print);
//    }
//    else {
//        printf("Error: ?U?¡Í ?i¡¤E?i?? ©«A¥ì¥ìC¨ª¨¬?¨«¨«¢¯a!\n");
//    }
//}


//A¡¾AO¡Æ¢® ¡ÆiA¡Ì¡ÆA
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
//        printf("Error: ?i¡¤E?i?? E¢çAICI¨«¨«¢¯a\n");
//        return;
//    }
//
//    if (strcmp(tokens[1], ">") == 0) {
//        if (token_count < 3 || tokens[2] == NULL) {
//            printf("Error: ¨¡AAI AI?¡×A¡í AO¡¤ACI¨«¨«¢¯a\n");
//            return;
//        }
//        char filePath[200];
//        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[2]);
//
//        FILE* newfile = fopen(filePath, "wt");
//        if (newfile == NULL) {
//            printf("Error: ¨¡AAI ¡íy¨«¨¬¢¯¢® ©«C¨¡¨¢C©¬©«A?I?U. Path: %s\n", filePath);
//            return;
//        } else {
//            printf("AO¡¤ACI¨«¨«¢¯a (A?¡¤a: Ctrl+D)\n");
//            while ((word = getchar()) != EOF) {
//                fputc(word, newfile);
//            }
//            fclose(newfile);
//        }
//    } else if (strcmp(tokens[1], "-n") == 0) {
//        if (token_count < 3 || tokens[2] == NULL) {
//            printf("Error: ¨¡AAI AI?¡×A¡í AO¡¤ACI¨«¨«¢¯a\n");
//            return;
//        }
//        char filePath[200];
//        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, tokens[2]);
//        FILE* file_print = fopen(filePath, "r");
//        if (file_print == NULL) {
//            printf("Error: ¨¡AAI ¢¯¡©¡¾a¢¯¢® ©«C¨¡¨¢C©¬©«A?I?U. Path: %s\n", filePath);
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
//            printf("Error: ¨¡AAI ¢¯¡©¡¾a¢¯¢® ©«C¨¡¨¢C©¬©«A?I?U. Path: %s\n", filePath);
//            return;
//        }
//        while (fgets(input, sizeof(input), file_print)) {
//            printf("%s", input);
//        }
//        fclose(file_print);
//    } else {
//        printf("Error: ?U?¡Í ?i¡¤E?i?? ©«A¥ì¥ìC¨ª¨¬?¨«¨«¢¯a!\n");
//    }
//}

// A¢æ?¡Æ?OAI ¡ÆiA¡Ì¡ÆA



void init_directory_tree(DirectoryTree* tree) {
    tree->root = (DirectoryNode*)malloc(sizeof(DirectoryNode));
    strcpy(tree->root->name, ".\\");  // Set root directory as current directory
    tree->root->type = 'd';
    tree->root->Parent = NULL;
    tree->root->LeftChild = NULL;
    tree->root->RightSibling = NULL;
    tree->current = tree->root;
}


void cat(DirectoryTree* tree, const char* token1, const char* token2) {
    char input[100];
    int ch;

    if (token1 == NULL) {
        printf("Error: No command provided.\n");
        return;
    }

    if (strcmp(token1, ">") == 0) {
        if (token2 == NULL) {
            printf("Error: Enter a file name.\n");
            return;
        } else {
            char filePath[200];
            snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, token2);
            printf("Creating file at path: %s\n", filePath);

            FILE* newfile = fopen(filePath, "w");
            if (newfile == NULL) {
                printf("Error: Failed to create a file. Path: %s\n", filePath);
                return;
            } else {
                printf("Enter (End: Ctrl+D)\n");
                while ((ch = getchar()) != EOF) {
                    fputc(ch, newfile);
                }
                fclose(newfile);
                printf("\nFile created successfully.\n");
                
                
                if(feof(stdin)){
                clearerr(stdin);
                }
            }
        }
    } else if (strcmp(token1, "-n") == 0) {
        if (token2 == NULL) {
            printf("Error: Enter a file name.\n");
            return;
        }
        char filePath[200];
        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, token2);
        printf("Opening file at path: %s\n", filePath);

        FILE* file_print = fopen(filePath, "r");
        if (file_print == NULL) {
            printf("Error: Failed to open a file. Path: %s\n", filePath);
            return;
        }
        int line_number = 1;
        while (fgets(input, sizeof(input), file_print)) {
            printf("%d  %s", line_number++, input);
        }
        fclose(file_print);
    } else {
        char filePath[200];
        snprintf(filePath, sizeof(filePath), "%s%s", tree->current->name, token1);
        printf("Opening file at path: %s\n", filePath);

        FILE* file_print = fopen(filePath, "r");
        if (file_print == NULL) {
            printf("Error: Failed to open a file. Path: %s\n", filePath);
            return;
        }
        while (fgets(input, sizeof(input), file_print)) {
            printf("%s", input);
        }
        fclose(file_print);
    }
}


