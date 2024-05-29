#include "../include/main.h"

int ChangeOwner(DirectoryTree* dirTree, char* userName, char* dirName, int flag) {
    DirectoryNode* tempNode = NULL;
    UserNode* tempUser = NULL;

    tempNode = FindDirectoryNode(dirTree, dirName, 'd');
    if (tempNode == NULL) {
        tempNode = FindDirectoryNode(dirTree, dirName, 'f');
        if (tempNode == NULL) {
            printf("chown: cannot access '%s': No such file or directory\n", dirName);
            return -1;
        }
    }

    tempUser = FindUserNode(userList, userName);
    if (tempUser == NULL) {
        printf("chown: invalid user '%s'\n", userName);
        return -1;
    }

    if (flag == 0) {
        tempNode->UserID = tempUser->UserID;
    }
    else {
        tempNode->GroupID = tempUser->GroupID;
    }

    return 0;
}
int ft_chown(DirectoryTree* dirTree, char* cmd) {
    pthread_t threadPool[MAX_THREAD];
    ThreadTree threadTree[MAX_THREAD];

    int thread_count = 0;
    char* command;
    char temp[MAX_NAME];

    if (cmd == NULL || strlen(cmd) == 0) {
        printf("chown: missing operand11\n");
        printf("Try 'chown --help' for more information.\n");
        return -1;
    }
    if (cmd[0] == '-') {
        if (strcmp(cmd, "--help") == 0) {
            printf("Usage: chown [OPTION]... [OWNER][:[GROUP]] FILE...\n");
            printf("    Change the owner and/or group of each FILE to OWNER and/or GROUP.\n\n");
            printf("Examples:\n");
            printf("  chown root /u\t Change the owner of /u to \"root\".\n");
            printf("  chown root:staff /u\t Likewise, but also change its group to \"staff\".\n");
            printf("  chown -hR root /u\t Change the owner of /u and subfiles to \"root\".\n\n");
        }
        else {
            printf("chown: invalid option '%s'\n", cmd);
            printf("Try 'chown --help' for more information22\n");
        }
        return -1;
    }
    char* saveptr;
    command = strtok_r(cmd, " ", &saveptr);
    if (command == NULL) {
        printf("Try 'chown --help' for more information.33\n");
        return -1;
    }
    strncpy(temp, command, MAX_NAME);
    command = strtok_r(NULL, " ", &saveptr);
    if (command == NULL) {
        printf("Try 'chown --help' for more information.444\n");
        return -1;
    }
    while (command && thread_count < MAX_THREAD) {
        threadTree[thread_count].threadTree = dirTree;
        threadTree[thread_count].username = strdup(temp);
        threadTree[thread_count++].command = strdup(command);
        command = strtok_r(NULL, " ", &saveptr);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_create(&threadPool[i], NULL, ChownThread, (void*)&threadTree[i]);
    }
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threadPool[i], NULL);
        free(threadTree[i].username);
        free(threadTree[i].command);
    }
    return 0;
}
void* ChownThread(void* arg) {
    ThreadTree* threadTree = (ThreadTree*)arg;
    DirectoryTree* dirTree = threadTree->threadTree;
    DirectoryNode* tmpNode = NULL;
    DirectoryNode* currentNode = dirTree->current;
    char* dirName = threadTree->command;
    char* username = threadTree->username;
    char* user_id = NULL;
    char* group_id = NULL;
    char tmp_dir[MAX_DIR];
    char tmp_user[MAX_NAME];

    strncpy(tmp_user, username, MAX_NAME);
    strncpy(tmp_dir, dirName, MAX_DIR);


    user_id = strtok(tmp_user, ":");
    group_id = strtok(NULL, ":");

    if (user_id == NULL && group_id == NULL) {
        printf("chown: invalid user: '%s'\n", username);
        pthread_exit(NULL);
    }

    if (strcmp(tmp_dir, "/") == 0) {
        printf("chown: changing ownership of the root directory '/' is not permitted\n");
        pthread_exit(NULL);
    }

    if (strstr(tmp_dir, "/") == NULL) {
        tmpNode = FindDirectoryNode(dirTree, tmp_dir, 'd');
        if (tmpNode == NULL) {
            tmpNode = FindDirectoryNode(dirTree, tmp_dir, 'f');
            if (tmpNode == NULL) {
                printf("chown: cannot access '%s': No such file or directory\n", tmp_dir);
                pthread_exit(NULL);
            }
        }
    }
    else {
        char* directoryPath = getDirectory(tmp_dir);
        if (directoryPath == NULL) {

            if (tmp_dir[0] == '/' && strchr(tmp_dir + 1, '/') == NULL) {
                directoryPath = "/";
            }
            else
            {
                printf("chown: cannot parse directory path from '%s'\n", tmp_dir);
                pthread_exit(NULL);
            }
        }

        char* fileName = strrchr(tmp_dir, '/');
        if (fileName != NULL) {
            fileName++;
        }
        else {
            fileName = tmp_dir;
        }

        if (ChangeDirectory(dirTree, directoryPath) != 0) {
            printf("chown: cannot access '%s': No such file or directory\n", directoryPath);
            free(directoryPath);
            pthread_exit(NULL);
        }
        free(directoryPath);


        tmpNode = FindDirectoryNode(dirTree, fileName, 'd');
        if (tmpNode == NULL) {
            tmpNode = FindDirectoryNode(dirTree, fileName, 'f');
            if (tmpNode == NULL) {
                printf("chown: cannot access '%s': No such file or directory\n", fileName);
                dirTree->current = currentNode;
                pthread_exit(NULL);
            }
        }
    }


    if (HasPermission(tmpNode, 'w') != 0) {
        printf("chown: changing ownership of '%s': Operation not permitted\n", tmp_dir);
        dirTree->current = currentNode;
        pthread_exit(NULL);
    }


    if (user_id != NULL) {
        ChangeOwner(dirTree, user_id, tmpNode->name, 0);
    }
    if (group_id != NULL) {
        ChangeOwner(dirTree, group_id, tmpNode->name, 1);
    }


    dirTree->current = currentNode;

    pthread_exit(NULL);
}