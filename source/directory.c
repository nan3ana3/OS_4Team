#include "../include/main.h"


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

//void DestroyDir(DirectoryNode* dirNode)
//{
//    if(dirNode->RightSibling != NULL){
//        DestroyDir(dirNode->RightSibling);
//    }
//    if(dirNode->LeftChild != NULL){
//        DestroyDir(dirNode->LeftChild);
//    }
//    dirNode->LeftChild = NULL;
//    dirNode->RightSibling = NULL;
//    DestroyNode(dirNode);
//}


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

DirectoryNode* IsExistDir(DirectoryTree* dirTree, char* dirName, char type)
{
    DirectoryNode* returnNode = NULL;

    returnNode = dirTree->current->LeftChild;
    while(returnNode != NULL){
        if(strcasecmp(returnNode->name, dirName) == 0 && returnNode->type == type)
            break;
        returnNode = returnNode->RightSibling;
    }
    return returnNode;
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

//char* getDir(char* dirPath)
//{
//    char* tmpPath = (char*)malloc(MAX_DIR);
//    char* directory = NULL;
//    char tmp[MAX_DIR];
//    char tmp2[MAX_DIR];
//
//    strncpy(tmp, dirPath, MAX_DIR);
//    directory = strtok(dirPath, "/");
//    while(directory != NULL){
//        strncpy(tmp2, directory, MAX_DIR);
//        directory  = strtok(NULL, "/");
//    }
//    strncpy(tmpPath, tmp, strlen(tmp)-strlen(tmp2)-1);
//    tmpPath[strlen(tmp)-strlen(tmp2)-1] = '\0';
//    return tmpPath;
//}

void SaveDir(DirectoryTree* dirTree, Stack* dirStack)
{

    Directory = fopen("Directory.txt", "w");
    WriteNode(dirTree, dirTree->root, dirStack);
    fclose(Directory);
}

DirectoryTree* LoadDir()
{
    DirectoryTree* dirTree = (DirectoryTree*)malloc(sizeof(DirectoryTree));
    char tmp[MAX_LENGTH];

    Directory = fopen("Directory.txt", "r");
    while(fgets(tmp, MAX_LENGTH, Directory) != NULL){
        ReadNode(dirTree, tmp);
    }
    fclose(Directory);
    dirTree->current = dirTree->root;
    return dirTree;
}