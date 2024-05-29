#include "../include/main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//directory.h getDir >> getDirectory

//directory.h (\ubcc0\uc218\uba85, \uc57d\uac04\uc758 \uc218\uc815) \ud568\uc218\uba85 ReadDir\uc5d0\uc11c \ubcc0\uacbd
int ReadDirectory(DirectoryTree* dirTree, char* line, char* dirName) {
    char* str; // \ubb38\uc790\uc5f4 \ud3ec\uc778\ud130
    char firstSegment[MAX_NAME]; // \uccab\ubc88\uc9f8 segment\ub97c \uc800\uc7a5\ud560 \ubc84\ud37c

    str = strtok(line, " "); // \ubb38\uc790\uc5f4\uc744 \ub744\uc5b4\uc4f0\uae30 \ub2e8\uc704\ub85c \ubd84\ub9ac
    if (str != NULL) {
        strncpy(firstSegment, str, MAX_NAME);
        firstSegment[MAX_NAME - 1] = '\0'; // \uc548\uc804\ud55c \uc885\ub8cc\ub97c \uc704\ud574 \ub110 \ubb38\uc790 \ucd94\uac00
    }

    for (int count = 0; count < 10; count++) {  // 10\ubc88 \ubc18\ubcf5
        str = strtok(NULL, " "); // \ub2e4\uc74c \ubb38\uc790\uc5f4 \ubd84\ub9ac
    }
    // \ub9c8\uc9c0\ub9c9 \ubb38\uc790\uc5f4\uc5d0 \ud574\ub2f9\ud558\ub294 \ubd80\ubd84\uc5d0 \ub3c4\ucc29
    if (str != NULL) { // \ubb38\uc790\uc5f4\uc774 \ub0a8\uc544 \uc788\ub294 \uacbd\uc6b0
        str[strlen(str) - 1] = '\0'; // \ubb38\uc790\uc5f4 \ub05d\uc5d0 NULL \ucd94\uac00, \ubb38\uc790\uc5f4 \uc885\ub8cc, \uac1c\ud589\ubb38\uc790\uc81c\uac70 
        char* found = strstr(str, dirName); // \ubb38\uc790\uc5f4 \uac80\uc0c9, \uc77c\uce58\ud558\ub294 \ubd80\ubd84 \ubb38\uc790\uc5f4\uc758 \uc2dc\uc791\uc8fc\uc18c \ubc18\ud658
        if (found) { // dirName\uacfc \uc77c\uce58\ud558\ub294 \ubb38\uc790\uc5f4\uc744 \ucc3e\uc740 \uacbd\uc6b0
            if (strcmp(str, "/") == 0) {
                printf("/%s\n", firstSegment); // \ub8e8\ud2b8 \ub514\ub809\ud1a0\ub9ac\uc778 \uacbd\uc6b0 \uacbd\ub85c \ucd9c\ub825
            } else {
                printf("%s/%s\n", found, firstSegment);  // \ub8e8\ud2b8 \ub514\ub809\ud1a0\ub9ac\uac00 \uc544\ub2cc \uacbd\uc6b0, found\uc640 firstSegment \uacb0\ud569, \uacbd\ub85c \ucd9c\ub825
            }
        }
    }
    return 0;
}

//directory.h (\ubcc0\uc218\uba85, \uc57d\uac04\uc758 \uc218\uc815) \ud568\uc218\uba85 FindDir\uc5d0\uc11c \ubcc0\uacbd
void FindDirectory(DirectoryTree* dirTree, char* dirName) {    // Directory.txt \ud30c\uc77c\uc744 \uc5f4\uace0 \uc9c0\uc815\ub41c \ub514\ub809\ud1a0\ub9ac \uc774\ub984\uc744 \uac80\uc0c9
    FILE* file = fopen("Directory.txt", "r"); // directory.txt \ud30c\uc77c\uc744 \uc77d\uae30\ubaa8\ub4dc\ub85c \uc5f4\uace0
    if (!file) {
        perror("No such file or directory");
        return;
    }
    char line[MAX_LENGTH]; // \ud30c\uc77c\uc5d0\uc11c \uc77d\uc740 \uac01 \uc904\uc744 \uc800\uc7a5\ud560 \uc784\uc2dc \ubc84\ud37c 
    while (fgets(line, sizeof(line), file)) { // \ud30c\uc77c\uc744 \ud55c \uc904\uc529 \uc77d\uace0 line\uc5d0 \uc800\uc7a5, ReadDirectory\ub97c \ud638\ucd9c\ud558\uc5ec \uac01 line\uc5d0\uc11c \ub514\ub809\ud1a0\ub9ac \uc774\ub984\uc744 \uac80\uc0c9\ud558\uace0 \uc77c\uce58\ud558\ub294 \uacbd\ub85c \ucd9c\ub825
        ReadDirectory(dirTree, line, dirName);
    }
    fclose(file);
}

// 1) \uba85\ub839\uc5b4\uc5d0 '/'\uac00 \ud3ec\ud568\ub418\uc9c0 \uc54a\uc740 \uacbd\uc6b0, \uc704\uce58\ud55c \ud604\uc7ac \ub514\ub809\ud1a0\ub9ac\uc5d0\uc11c \ud30c\uc77c\uc774\ub098 \ub514\ub809\ud1a0\ub9ac \uac80\uc0c9
// 2) \uba85\ub839\uc5b4\uc5d0 '/'\uac00 \ud3ec\ud568\ub418\uc5b4 \uc788\ub294 \uacbd\uc6b0, \ud30c\uc77c\uc774\ub098 \ub514\ub809\ud1a0\ub9ac \uac80\uc0c9
// 2-1) \uacbd\ub85c\uac00 \uc798\ubabb\ub410\uc744 \uacbd\uc6b0,
// 2-2) \uacbd\ub85c\uac00 \uc62c\ubc14\ub974\ub098, \ud30c\uc77c\uc774\ub098 \ub514\ub809\ud1a0\ub9ac\uac00 \uc5c6\uc744 \uacbd\uc6b0
void* FindThread(void* arg) {
    ThreadTree* threadTree = (ThreadTree*)arg; // \uc2a4\ub808\ub4dc \uc815\ubcf4\uc640 \uba85\ub839\uc744 \ud3ec\ud568\ud558\ub294 \uad6c\uc870\uccb4
    DirectoryTree* dirTree = threadTree->threadTree; // \ub514\ub809\ud1a0\ub9ac \ud2b8\ub9ac \uc811\uadfc
    char* cmd = threadTree->command; // \uc2e4\ud589\ud560 \uba85\ub839
    char fullPath[MAX_DIR]; // \uc804\uccb4 \uacbd\ub85c\ub97c \uc800\uc7a5\ud560 \ubc84\ud37c
    char* fileName; // \ud30c\uc77c \uc774\ub984
    char* dirPath; // \ub514\ub809\ud1a0\ub9ac \uacbd\ub85c
    int dirCheck; // \ub514\ub809\ud1a0\ub9ac \ubcc0\uacbd \uc131\uacf5 \uc5ec\ubd80 \ud655\uc778
    DirectoryNode* currentNode = dirTree->current; // \ud604\uc7ac \ub514\ub809\ud1a0\ub9ac \uc704\uce58 \uc800\uc7a5

    strncpy(fullPath, cmd, MAX_DIR); // \uba85\ub839\uc5b4\uc5d0\uc11c \uc804\uccb4 \uacbd\ub85c \ubcf5\uc0ac
    fullPath[MAX_DIR - 1] = '\0'; // \ub110 \uc885\ub8cc \ubb38\uc790 \ubcf4\uc7a5

    // \ud30c\uc77c \uc774\ub984\uacfc \ub514\ub809\ud1a0\ub9ac \uacbd\ub85c \ubd84\ub9ac
    fileName = strrchr(fullPath, '/');
    if (fileName) {
        fileName++; // '/' \ub2e4\uc74c \ubb38\uc790\ub85c \ud30c\uc77c \uc774\ub984 \uc2dc\uc791
        dirPath = fullPath;
        *(fileName - 1) = '\0'; // \ud30c\uc77c \uc774\ub984 \uc55e\uc5d0\uc11c \ubb38\uc790\uc5f4 \uc885\ub8cc\ub85c \ub514\ub809\ud1a0\ub9ac \uacbd\ub85c \uc124\uc815
    } else {
        fileName = fullPath; // '/'\uac00 \uc5c6\ub294 \uacbd\uc6b0, \uc804\uccb4 \uba85\ub839\uc774 \ud30c\uc77c \uc774\ub984
        dirPath = ".";
    }

    // \ud544\uc694\ud55c \uacbd\uc6b0 \ub514\ub809\ud1a0\ub9ac \ubcc0\uacbd
    if (strcmp(dirPath, ".") != 0) {
        dirCheck = ChangeDirectory(dirTree, dirPath);
        if (dirCheck != 0) {
            threadTree->found = 0; // \ub514\ub809\ud1a0\ub9ac \ubcc0\uacbd \uc2e4\ud328
            pthread_exit(NULL);
        }
    }

    // \ud30c\uc77c \ub610\ub294 \ub514\ub809\ud1a0\ub9ac \uc874\uc7ac \uc5ec\ubd80 \ud655\uc778
    if (!FindDirectoryNode(dirTree, fileName, 'd') && !FindDirectoryNode(dirTree, fileName, 'f')) {
        threadTree->found = 0; // \ub514\ub809\ud1a0\ub9ac\ub098 \ud30c\uc77c\uc774 \uc5c6\uc74c
    } else {
        threadTree->found = 1; // \ub514\ub809\ud1a0\ub9ac\ub098 \ud30c\uc77c\uc774 \uc788\uc74c
        threadTree->command = strdup(cmd); // \uc804\uccb4 \uba85\ub839\uc5b4 \uc800\uc7a5
    }

    // \ud604\uc7ac \ub514\ub809\ud1a0\ub9ac\ub97c \uc774\uc804 \uc0c1\ud0dc\ub85c \ubcf5\uc6d0
    dirTree->current = currentNode;
    pthread_exit(NULL);
}


int find(DirectoryTree* dirTree, char* cmd) {
    pthread_t ThreadArr[MAX_THREAD]; // thread \uc2dd\ubcc4\uc790 \ubc30\uc5f4
    ThreadTree ThreadTree[MAX_THREAD]; // thread\ubcc4 \uc791\uc5c5 \uc815\ubcf4 \ubc30\uc5f4 / threadtree \uad6c\uc870\uccb4 \ubc30\uc5f4
    char* command; // \uba85\ub839\uc5b4 \uc800\uc7a5 \ud3ec\uc778\ud130
    int ThreadCount = 0; // \uc0dd\uc131\ub41c thread \uc218

    // find . and find -- \uc778 \uacbd\uc6b0, \ud604\uc7ac \ub514\ub809\ud1a0\ub9ac\uc5d0\uc11c FindDirectory \ud638\ucd9c
    if (cmd == NULL || strcmp(cmd, ".") == 0 || strcmp(cmd, "--") == 0) {
        FindDirectory(dirTree, dirTree->current->name); // \ud604\uc7ac \ub514\ub809\ud1a0\ub9ac \uac80\uc0c9
        return 0;
    } else if (cmd[0] == '-') { // \uba85\ub839\uc5b4\uac00 \ub300\uc2dc(-)\ub85c \uc2dc\uc791\ud558\uba74(\uc635\uc158\uc778 \uacbd\uc6b0)
        if (strcmp(cmd, "--help") == 0) { // \uba85\ub839\uc5b4\uac00 --help\uc778\uc9c0 \ud655\uc778\ud558\uace0 \uc0ac\uc6a9\ubc95\uacfc \uc635\uc158\uc5d0 \ub300\ud55c \ub3c4\uc6c0\ub9d0\uc744 \ucd9c\ub825
            printf("Usage: find [OPTION] [path...] [expression]\n\n");
            printf("    Search for files in a directory hierarchy.\n\n");
            printf("    Options:\n");
            printf("       .         Search for files in the current directory\n");
            printf("       --        Search for files in the current directory\n");
            printf("       --help    display this help and exit\n");
            printf("default path is the current directory; default expression is -print\n");

            return -1;
        } else { // \uc720\ud6a8\ud558\uc9c0 \uc54a\uc740 \uc635\uc158\uc778 \uacbd\uc6b0 \uc624\ub958 \uba54\uc138\uc9c0\uc640 \ub3c4\uc6c0\ub9d0 \ucd9c\ub825
            char* invalid_option = strchr(cmd, '-');
            printf("find: unknown predicate '%s'\n", invalid_option); // \uc624\ub958 \uba54\uc2dc\uc9c0
            printf("Try 'find --help' for more information.\n"); // \ub3c4\uc6c0\ub9d0 \uc548\ub0b4
            return -1;
        }
    } else { // threadTree \ubc30\uc5f4\uc744 \ubc18\ubcf5\ud558\uba70, \uac01 \uba85\ub839\uc5b4\uc5d0 \ub300\ud574 \uc0c8\ub85c\uc6b4 \uc2a4\ub808\ub4dc\ub97c \uc0dd\uc131\ud558\uace0(pthread_create), \uac01 \uc2a4\ub808\ub4dc\uac00 \uc644\ub8cc\ub420 \ub54c\uae4c\uc9c0 \uae30\ub2e4\ub9bc(pthread_join).
        char* saveptr;
        command = strtok_r(cmd, " ", &saveptr); // cmd\uc5d0\uc11c \uccab \ubc88\uc9f8 \uba85\ub839\uc5b4 \ubd84\ub9ac
        while (command != NULL && ThreadCount < MAX_THREAD) { // \uba85\ub839\uc5b4\uac00 \ub0a8\uc544\uc788\ub294 \ub3d9\uc548 \ubc18\ubcf5
            ThreadTree[ThreadCount].threadTree = dirTree; // \ud604\uc7ac \ub514\ub809\ud1a0\ub9ac \ud2b8\ub9ac \uc124\uc815
            ThreadTree[ThreadCount].command = strdup(command); // \uba85\ub839\uc5b4 \uc124\uc815
            ThreadTree[ThreadCount].found = -1; // \ucd08\uae30 \uc0c1\ud0dc\ub97c \uc124\uc815
            pthread_create(&ThreadArr[ThreadCount], NULL, FindThread, (void*)&ThreadTree[ThreadCount]);
            ThreadCount++;
            command = strtok_r(NULL, " ", &saveptr); // \ub2e4\uc74c \uba85\ub839\uc5b4 \ubd84\ub9ac
        }

        // \ubaa8\ub4e0 \uc2a4\ub808\ub4dc\ub97c \uc0dd\uc131\ud55c \ud6c4, \uac01 \uc2a4\ub808\ub4dc\uc758 \uc885\ub8cc\ub97c \uae30\ub2e4\ub9bc
        for (int i = 0; i < ThreadCount; i++) {
            pthread_join(ThreadArr[i], NULL);
        }

        // \ubaa8\ub4e0 \uc2a4\ub808\ub4dc\uac00 \uc644\ub8cc\ub41c \ud6c4, \uc2e4\uc81c \ucd9c\ub825\uc744 \uc218\ud589
        for (int i = 0; i < ThreadCount; i++) {
            if (ThreadTree[i].found == 1) {
                printf("%s\n", ThreadTree[i].command);
                FindDirectory(dirTree, ThreadTree[i].command); // \ub514\ub809\ud1a0\ub9ac\uac00 \uc788\ub294 \uacbd\uc6b0 \uacbd\ub85c \uac80\uc0c9 \ubc0f \ucd9c\ub825
            } else if (ThreadTree[i].found == 0) {
                printf("find: '%s': No such file or directory.\n", ThreadTree[i].command);
            }
           
            free(ThreadTree[i].command); // strdup\ub85c \ud560\ub2f9\ub41c \uba54\ubaa8\ub9ac \ud574\uc81c
        }
    }

    return 0;
}

