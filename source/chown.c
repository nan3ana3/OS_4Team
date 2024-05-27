#include "../include/main.h"

// ��ο� �ش��ϴ� ���丮 ��带 ã�� �Լ�
DirectoryNode* IsDir(DirectoryTree* dirtree, const char* path) {
    DirectoryNode* current = dirtree->root;
    char path_copy[256];
    strcpy_s(path_copy, sizeof(path_copy), path);
    char* context = NULL;
    char* token = strtok_s(path_copy, "/", &context);

    while (token != NULL && current != NULL) {
        DirectoryNode* child = current->LeftChild;
        while (child != NULL) {
            if (strcmp(child->name, token) == 0) {
                current = child;
                break;
            }
            child = child->RightSibling;
        }
        if (child == NULL) {
            current = NULL;
        }
        token = strtok_s(NULL, "/", &context);
    }
    return current;
}

void chown_command(DirectoryTree* dirtree, char* cmd) {
    char* context = NULL;
    char* command = strtok_s(cmd, " ", &context);
    if (strcmp(command, "chown") != 0) {
        printf("Invalid command\n");
        return;
    }

    char* option = strtok_s(NULL, " ", &context);
    if (strcmp(option, "-d") == 0) {
        char* path = strtok_s(NULL, "", &context);
        UncompressDir(dirtree, path);
        return;
    }

    char* path = strtok_s(NULL, "", &context);
    DirectoryNode* tmp = IsDir(dirtree, path);
    if (tmp == NULL) {
        printf("�߸��� ���丮\n");
        return;
    }
    char* userContext = NULL;
    char* User = strtok_s(option, ":", &userContext);
    char* Group = strtok_s(NULL, "", &userContext);
    if (User != NULL) {
        tmp->UserID = atoi(User);
    }
    if (Group != NULL) {
        tmp->GroupID = atoi(Group);
    }
}

void MoveDir(DirectoryTree* dirtree, const char* srcPath, const char* destPath) {
    DirectoryNode* srcNode = IsDir(dirtree, srcPath);
    DirectoryNode* destNode = IsDir(dirtree, destPath);

    if (srcNode == NULL || destNode == NULL) {
        printf("�ҽ� �Ǵ� ��� ���丮�� ã�� �� �����ϴ�\n");
        return;
    }

    // ���� �θ��� �ڽ� ��Ͽ��� srcNode�� ����
    DirectoryNode* parent = srcNode->Parent;
    if (parent != NULL) {
        DirectoryNode* child = parent->LeftChild;
        DirectoryNode* prev = NULL;
        while (child != NULL && child != srcNode) {
            prev = child;
            child = child->RightSibling;
        }
        if (child == srcNode) {
            if (prev == NULL) {
                parent->LeftChild = srcNode->RightSibling;
            }
            else {
                prev->RightSibling = srcNode->RightSibling;
            }
        }
    }

    // destNode�� �ڽ� ��Ͽ� srcNode�� �߰�
    srcNode->Parent = destNode;
    srcNode->RightSibling = destNode->LeftChild;
    destNode->LeftChild = srcNode;
}

void UncompressDir(DirectoryTree* dirtree, const char* path) {
    DirectoryNode* node = IsDir(dirtree, path);
    if (node == NULL) {
        printf("���丮�� ã�� �� �����ϴ�\n");
        return;
    }

    // ���� ����: ���丮�� ���� �����Ǿ��ٰ� ���
    printf("���丮 %s ���� ������\n", path);

    // ���� ���� ���� ������ ���⼭ ����
}
