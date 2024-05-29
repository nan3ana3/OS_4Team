#include "../include/main.h"

char* PrintDirectoryPath(DirectoryTree* dirTree) {
    DirectoryNode* current = dirTree->current;
    char* path = (char*)malloc(MAX_DIR * 2); // ���� �޸� �Ҵ�
    if (path == NULL) {
        return NULL; // �޸� �Ҵ� ���� �� NULL ��ȯ
    }
    strcpy(path, "/"); // ��Ʈ ���丮�� �ʱ�ȭ

    char* segments[MAX_DIR]; // ���丮 �̸� ���� ������
    int segmentCount = 0; // ���׸�Ʈ ��

    // ��Ʈ ���丮�� ������ ������ �ݺ�
    while (current != dirTree->root) {
        segments[segmentCount++] = current->name; // ���丮 �̸��� �迭�� ����
        current = current->Parent; // ���� ���丮�� �̵�
    }

    // ��θ� �������� �����Ͽ� ���� ��� ����
    for (int i = segmentCount - 1; i >= 0; --i) {
        strncat(path, segments[i], MAX_DIR * 2 - strlen(path) - 1);
        if (i > 0) { // ������ ���׸�Ʈ �ڿ��� �����ø� �߰����� ����
            strncat(path, "/", MAX_DIR * 2 - strlen(path) - 1);
        }
    }

    return path;
}

void pwd(DirectoryTree* dirTree, char* cmd) {
    if (cmd == NULL || strcmp(cmd, "") == 0)
    {
        // �⺻ ��ɾ� pwd
        char* path = PrintDirectoryPath(dirTree);
        if (path != NULL) {
            printf("%s\n", path);
            free(path);
        }
    }
    else if (cmd[0] == '-')
    {
        if (strcmp(cmd, "-") == 0 || strcmp(cmd, "--") == 0)
        {
            // �⺻ ��ɾ� pwd, pwd -, pwd -- ��� ���� ��� ���
            char* path = PrintDirectoryPath(dirTree);
            if (path != NULL) 
            {
                printf("%s\n", path);
                free(path);
            }
        }
        else if (strcmp(cmd,"--help") == 0) {
            // pwd --help
            printf("Usage: pwd [OPTION]\n");
            printf("    Print the name of the current working directory.\n\n");
            printf("    Options:\n");
            printf("       -         print the name of the current working directory\n");
            printf("       --        print the name of the current working directory\n");
            printf("       --help    display this help and exit\n");
        }
        else 
        {
            // �߸��� �ɼ� ���� �޽��� ��� ex)pwd -aa
            printf("bash: pwd: %s: invalid option\n", cmd);
            printf("Try 'pwd --help' for more information.\n");
        }
    }
    else
    { 
        char* path = PrintDirectoryPath(dirTree);
            if (path != NULL) 
            {
                printf("%s\n", path);
                free(path);
            }
     //pwd �� �����̿����� ��� x ���� ���丮 ��ġ ���
    }
}