#include "../include/main.h"

// 재귀적으로 디렉토리 노드를 삭제
void DestroyDir(DirectoryNode* dirNode) 
{
    if(dirNode->RightSibling != NULL){
        DestroyDir(dirNode->RightSibling);
    }
    if(dirNode->LeftChild != NULL){
        DestroyDir(dirNode->LeftChild);
    }
    dirNode->LeftChild = NULL;
    dirNode->RightSibling = NULL;
    DestroyNode(dirNode); //유틸리티에 있음, 현재 노드를 삭제함
}

// 주어진 이름과 타입의 디렉토리 노드가 현재 디렉토리의 자식 노드들 중에 존재하는 지 확인
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

// 경로 문자열에서 디렉토리 이름을 추출, 경로 반환
char* getDir(char* dirPath)
{
    char* tmpPath = (char*)malloc(MAX_DIR);
    char* directory = NULL;
    char tmp[MAX_DIR];
    char tmp2[MAX_DIR];

    strncpy(tmp, dirPath, MAX_DIR);
    directory = strtok(dirPath, "/");
    while(directory != NULL){
        strncpy(tmp2, directory, MAX_DIR);
        directory  = strtok(NULL, "/");
    }
    strncpy(tmpPath, tmp, strlen(tmp)-strlen(tmp2)-1);
    tmpPath[strlen(tmp)-strlen(tmp2)-1] = '\0';
    return tmpPath;
}

// 디렉토리 트리를 파일에 저장
void SaveDir(DirectoryTree* dirTree, Stack* dirStack)
{

    Directory = fopen("Directory.txt", "w");
    WriteNode(dirTree, dirTree->root, dirStack);
    fclose(Directory);
}

// 파일에서 디렉토리 트리를 로드함
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