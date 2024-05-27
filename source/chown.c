#include "../include/main.h"

// 경로에 해당하는 디렉토리 노드를 찾는 함수
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
        printf("잘못된 디렉토리\n");
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
        printf("소스 또는 대상 디렉토리를 찾을 수 없습니다\n");
        return;
    }

    // 현재 부모의 자식 목록에서 srcNode를 제거
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

    // destNode의 자식 목록에 srcNode를 추가
    srcNode->Parent = destNode;
    srcNode->RightSibling = destNode->LeftChild;
    destNode->LeftChild = srcNode;
}

void UncompressDir(DirectoryTree* dirtree, const char* path) {
    DirectoryNode* node = IsDir(dirtree, path);
    if (node == NULL) {
        printf("디렉토리를 찾을 수 없습니다\n");
        return;
    }

    // 더미 구현: 디렉토리가 압축 해제되었다고 출력
    printf("디렉토리 %s 압축 해제됨\n", path);

    // 실제 압축 해제 로직을 여기서 구현
}
