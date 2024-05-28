#include "../include/main.h"


DirectoryNode* FindDirectoryNode(DirectoryTree* dirTree, char* dirName, char type) {
    DirectoryNode* currentNode = dirTree->current->LeftChild; // ���� ���丮�� ù ��° �ڽ� ���� ����

    // ��� �ڽ� ��带 Ž��
    while (currentNode != NULL) {
        // ���丮 �̸��� ������ ��ġ�ϸ� ��带 ��ȯ
        if (strcmp(currentNode->name, dirName) == 0 && currentNode->type == type) {
            return currentNode;
        }
        // ���� ���� ���� �̵�
        currentNode = currentNode->RightSibling;
    }
    // ��ġ�ϴ� ��带 ã�� ���ϸ� NULL ��ȯ
    return NULL;
}

char* getDirectory(const char* fullPath) {
    char* DirectoryPath = (char*)malloc(MAX_DIR);
    if (DirectoryPath == NULL) {
        return NULL;  // �޸� �Ҵ� ���� �� NULL ��ȯ
    }

    // strrchr �Լ��� ����Ͽ� ��ο��� ������ '/' ã��
    const char* lastSlash = strrchr(fullPath, '/');
    if (lastSlash == NULL || lastSlash == fullPath) {
        free(DirectoryPath);
        return NULL;  // '/'�� ���ų� �� ó������ �ִ� ���
    }

    // ������ '/' ���������� ���ڿ��� ����
    int pathLength = lastSlash - fullPath;
    strncpy(DirectoryPath, fullPath, pathLength);
    DirectoryPath[pathLength] = '\0'; // ���ڿ� ���� ���� ���

    return DirectoryPath;
}

void DestroyDir(DirectoryNode* dirNode) {
    if (dirNode == NULL) return;

    DirectoryNode* current = dirNode->LeftChild;
    while (current != NULL) {
        DirectoryNode* next = current->RightSibling;
        DestroyDir(current);
        current = next;
    }

    DestroyNode(dirNode);
}

void SaveDir(DirectoryTree* dirTree)
{

    Directory = fopen("Directory.txt", "w");
    WriteNode(dirTree, dirTree->root);
    fclose(Directory);
}

DirectoryTree* LoadDir()
{
    DirectoryTree* dirTree = (DirectoryTree*)malloc(sizeof(DirectoryTree));
    char line[MAX_LENGTH];

    Directory = fopen("Directory.txt", "r");
    while (fgets(line, sizeof(line), Directory) != NULL) {
        ReadNode(dirTree, line);
    }
    fclose(Directory);
    dirTree->current = dirTree->root;
    return dirTree;
}