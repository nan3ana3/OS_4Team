#include "../include/main.h"


DirectoryNode* FindDirectoryNode(DirectoryTree* dirTree, char* dirName, char type) {
    DirectoryNode* currentNode = dirTree->current->LeftChild; // 현재 디렉토리의 첫 번째 자식 노드로 설정

    // 모든 자식 노드를 탐색
    while (currentNode != NULL) {
        // 디렉토리 이름과 유형이 일치하면 노드를 반환
        if (strcmp(currentNode->name, dirName) == 0 && currentNode->type == type) {
            return currentNode;
        }
        // 다음 형제 노드로 이동
        currentNode = currentNode->RightSibling;
    }
    // 일치하는 노드를 찾지 못하면 NULL 반환
    return NULL;
}

char* getDirectory(const char* fullPath) {
    char* DirectoryPath = (char*)malloc(MAX_DIR);
    if (DirectoryPath == NULL) {
        return NULL;  // 메모리 할당 실패 시 NULL 반환
    }

    // strrchr 함수를 사용하여 경로에서 마지막 '/' 찾기
    const char* lastSlash = strrchr(fullPath, '/');
    if (lastSlash == NULL || lastSlash == fullPath) {
        free(DirectoryPath);
        return NULL;  // '/'가 없거나 맨 처음에만 있는 경우
    }

    // 마지막 '/' 이전까지의 문자열을 복사
    int pathLength = lastSlash - fullPath;
    strncpy(DirectoryPath, fullPath, pathLength);
    DirectoryPath[pathLength] = '\0'; // 문자열 종료 지점 명시

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