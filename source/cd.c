#include "../include/main.h"

char previousPath[MAX_DIR * 2]= "";
int cd(DirectoryTree* dirTree, char* cmd) {
    DirectoryNode* tempNode = NULL;
    char temp[MAX_DIR];
    char* currentPath;
    int check;

    // ���� ��θ� �����Ͽ� ������ ��ġ�� ��η� ���
    currentPath = PrintDirectoryPath(dirTree);

    // cmd . or cmd
    if (cmd == NULL || strcmp(cmd, ".") == 0) {
        check = ChangeDirectory(dirTree, ".");
    } else if (strcmp(cmd, "~") == 0) { // cmd ~ : Ȩ ���丮�� �̵�
        strcpy(temp, userList->current->dir);
        check = ChangeDirectory(dirTree, temp);
    } else if (strcmp(cmd, "/") == 0) {
        check = ChangeDirectory(dirTree, "/");
    } else if (strcmp(cmd, "..") == 0) {
        check = ChangeDirectory(dirTree, "..");
    } else if (cmd[0] == '-') { // �ɼ��� ���� ���
        if (strcmp(cmd, "--help") == 0) {
            printf("Usage: cd [OPTION] [DIRECTORY]\n");
            printf("    Change the shell working directory.\n\n");
            printf("    Change the current directory to DIR.  The default DIR is the value of the Home shell variable.\n\n");
            printf("    Options:\n");
            printf("       ~     Go to the home directory of the current user\n");
            printf("       -     Switch to the previous directory\n");
            printf("       /     Change to the root directory\n");
            printf("       .     Remain in the current directory\n");
            printf("       ..    Move up to the parent directory\n");
            printf("       --help     display this help and exit\n");
            free(currentPath);
            return 0;
        } else if (strcmp(cmd, "-") == 0) {
            if (previousPath[0] == '\0') {
                printf("OLDPWD not set\n");
                free(currentPath);
                return -1;
            }
            printf("%s\n", previousPath);
            check = ChangeDirectory(dirTree, previousPath);
        } else {
            // �� ���� �ɼǵ� ���� ó��
            printf("bash: cd: %s: invalid option\n", cmd);
            printf("Try 'cd --help' for more information.\n");
            free(currentPath);
            return -1;
        }
    } else { // �ɼ��� ���� ���
        check = ChangeDirectory(dirTree, cmd);
    }

    // ���� ��� ������Ʈ
    if (check == 0) { // ���丮 ������ ������ ���
        strncpy(previousPath, currentPath, sizeof(previousPath) - 1);
        previousPath[sizeof(previousPath) - 1] = '\0';
    }
    free(currentPath);

    return 0;
}
int ChangeDirectory(DirectoryTree* dirTree, char* dirPath) {
    DirectoryNode* tempNode = NULL;
    DirectoryNode* savedNode = dirTree->current;  // ���� ���丮 ��带 �ӽ� ������ ����
    char tempPath[MAX_DIR];
    char* command = NULL;

    // ���� ���丮 ('.')�� ���: �ƹ� �۾��� ���� ����
    if (strcmp(dirPath, ".") == 0) {
        return 0;
    }

    // ���� ���丮�� �̵��ϴ� ��� ('..')
    if (strcmp(dirPath, "..") == 0) {
        if (dirTree->current != dirTree->root) { // ���� ���丮�� ��Ʈ ���丮�� �ƴϸ� ���� ���丮�� �̵�
            dirTree->current = dirTree->current->Parent;
        }
        return 0;
    }

    // ��θ� tempPath�� ����
    strncpy(tempPath, dirPath, MAX_DIR - 1); // ���ڿ� ����
    tempPath[MAX_DIR - 1] = '\0';

    // ���� ����� ���
    if (dirPath[0] == '/') {
        dirTree->current = dirTree->root; // ���� ���丮 = ��Ʈ ���丮
        command = strtok(tempPath + 1, "/"); // ù��° ���丮 �̸� ����
    } else {  // ��� ����� ���
        command = strtok(tempPath, "/"); // ù��° ���丮 �̸� ����
    }

    // ��θ� �ϳ��� Ž���ϸ� �̵�
    while (command != NULL) {
        // ���� ���丮�� �̵��ϴ� ���
        tempNode = FindDirectoryNode(dirTree, command, 'd'); // �ش� �̸��� ���丮�� �����ϸ� �̵�
        if (tempNode != NULL) {
            dirTree->current = tempNode;
        } else {
            // ���丮�� �������� ���� ���
            dirTree->current = savedNode; // ���� ���丮 ����
            printf("cd: %s: No such file or directory\n", command);
            return -1;
        }
        command = strtok(NULL, "/");
    }

    return 0;
}
