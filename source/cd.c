#include "../include/main.h"

char previousPath[MAX_DIR * 2] = ""; // ���� ��θ� ������ ����

////permission.h
//int CheckPermission(const int* permissions, char pms, int index) {
//    switch (pms) {
//    case 'r': return permissions[index] ? 0 : -1; // �б� ���� Ȯ��
//    case 'w': return permissions[index + 1] ? 0 : -1; // ���� ���� Ȯ��
//    case 'x': return permissions[index + 2] ? 0 : -1; // ���� ���� Ȯ��
//    default: return -1; // �߸��� ���� ��û
//    }
//}
////permission.h
//int HasPermission(DirectoryNode* dirNode, char pms)
//{
//    // userList�� current ����ڰ� NULL���� Ȯ��
//    if (userList == NULL || userList->current == NULL) {
//        return -1; // ������ ���� �ڵ� ��ȯ
//    }
//
//    // ������ (��Ʈ �����)�� ��� ������ ����
//    if (userList->current->UserID == 0) {
//        return 0;
//    }
//    // �������� ������ Ȯ��
//    if (userList->current->UserID == dirNode->UserID) {
//        return CheckPermission(dirNode->permission, pms, 0);
//    }
//
//    // �׷��� ������ Ȯ��
//    if (userList->current->GroupID == dirNode->GroupID) {
//        return CheckPermission(dirNode->permission, pms, 3);
//    }
//
//    // ��Ÿ ������� ������ Ȯ��
//    return CheckPermission(dirNode->permission, pms, 6);
//}
//
//DirectoryNode* FindDirectoryNode(DirectoryTree* dirTree, char* dirName, char type) {
//    DirectoryNode* currentNode = dirTree->current->LeftChild; // ���� ���丮�� ù ��° �ڽ� ���� ����
//
//    // ��� �ڽ� ��带 Ž��
//    while (currentNode != NULL) {
//        // ���丮 �̸��� ������ ��ġ�ϸ� ��带 ��ȯ
//        if (strcmp(currentNode->name, dirName) == 0 && currentNode->type == type) {
//            return currentNode;
//        }
//        // ���� ���� ���� �̵�
//        currentNode = currentNode->RightSibling;
//    }
//    // ��ġ�ϴ� ��带 ã�� ���ϸ� NULL ��ȯ
//    return NULL;
//}


int ChangeDirectory(DirectoryTree* dirTree, char* dirPath) {
    // ���� ����
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

    // �ֻ��� ���丮�� ���
    if (strcmp(dirPath, "/") == 0) {
        dirTree->current = dirTree->root; // ���� ���丮 = ��Ʈ ���丮
        return 0;
    }

    // ���� ����� ���
    if (dirPath[0] == '/') {
        dirTree->current = dirTree->root; // ���� ���丮 = ��Ʈ ���丮
        command = strtok(tempPath + 1, "/"); // ù��° ���丮 �̸� ����
    }
    else {  // ��� ����� ���
        command = strtok(tempPath, "/"); // ù��° ���丮 �̸� ����
    }

    // ��θ� �ϳ��� Ž���ϸ� �̵�
    while (command != NULL) {
        // ���� ���丮�� �̵��ϴ� ���
        tempNode = FindDirectoryNode(dirTree, command, 'd');// �ش� �̸��� ���丮�� �����ϸ� �̵�
        if (tempNode != NULL) {
            dirTree->current = tempNode;
        }
        else {
            // ���丮�� �������� ���� ���
            dirTree->current = savedNode; // ���� ���丮 ����
            return -1;
        }
        command = strtok(NULL, "/");
    }

    return 0;
}

////pwd.h
//char* PrintDirectoryPath(DirectoryTree* dirTree) {
//    DirectoryNode* current = dirTree->current;
//    char* path = (char*)malloc(MAX_DIR * 2); // ���� �޸� �Ҵ�
//    if (path == NULL) {
//        return NULL; // �޸� �Ҵ� ���� �� NULL ��ȯ
//    }
//    strcpy(path, "/"); // ��Ʈ ���丮�� �ʱ�ȭ
//
//    char* segments[MAX_DIR]; // ���丮 �̸� ���� ������
//    int segmentCount = 0; // ���׸�Ʈ ��
//
//    // ��Ʈ ���丮�� ������ ������ �ݺ�
//    while (current != dirTree->root) {
//        segments[segmentCount++] = current->name; // ���丮 �̸��� �迭�� ����
//        current = current->Parent; // ���� ���丮�� �̵�
//    }
//
//    // ��θ� �������� �����Ͽ� ���� ��� ����
//    for (int i = segmentCount - 1; i >= 0; --i) {
//        strncat(path, segments[i], MAX_DIR * 2 - strlen(path) - 1);
//        if (i > 0) { // ������ ���׸�Ʈ �ڿ��� �����ø� �߰����� ����
//            strncat(path, "/", MAX_DIR * 2 - strlen(path) - 1);
//        }
//    }
//
//    return path;
//}

int cd(DirectoryTree* dirTree, char* cmd) {
    DirectoryNode* tempNode = NULL;
    char temp[MAX_DIR];
    char* currentPath;
    int check;
    // ���� ��θ� �����Ͽ� ������ ��ġ�� ��η� ���
    currentPath = PrintDirectoryPath(dirTree);
    // �ڽ��� Ȩ ���丮�� �̵�
    if (cmd == NULL || strcmp(cmd, "~") == 0) {
        strcpy(temp, userList->current->dir);
        check = ChangeDirectory(dirTree, temp);
    }
    else if (cmd[0] == '-') //�ɼ��� ������� 
    {
        if (strcmp(cmd, "--help") == 0)
        {
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
        }
        else if (strcmp(cmd, "-") == 0)
        {
            if (previousPath[0] == '\0') {
                printf("OWD PWD NOT SET\n");
                free(currentPath);
                return -1;
            }
            printf("%s\n", previousPath);
            check = ChangeDirectory(dirTree, previousPath);
        }
        else
        {
            cmd = strtok(cmd, "-");     // �� ���� �ɼǵ� ���� ó��
            printf("bash: cd: %s: invalid option\n", cmd);
            printf("Try 'cd --help' for more information.\n");
            free(currentPath);
            return -1;

        }
    }
    else //�ɼ��� ���� ��� 
    {
        tempNode = FindDirectoryNode(dirTree, cmd, 'd');
        if (tempNode != NULL) {
            if (HasPermission(tempNode, 'x') != 0) {       //���ٱ����� �źεǾ� ���� ���
                printf("cd: %s: Permission denied\n", cmd);
                free(currentPath);
                return -1;
            }
        }
        else {
            // ���丮�� ã�� ���� ���
            printf("cd: %s: No such file or directory\n", cmd);
            free(currentPath);
            return -1;
        }
        check = ChangeDirectory(dirTree, cmd);

    }

    // ���� ��� ������Ʈ
    if (check == 0) //���丮 ������ ������ ���,
    {
        strncpy(previousPath, currentPath, sizeof(previousPath) - 1);
        previousPath[sizeof(previousPath) - 1] = '\0';
    }
    free(currentPath);

    return 0;
}


