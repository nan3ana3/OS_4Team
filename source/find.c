#include "../include/main.h"

//#define MAX_THREAD 10
//#define MAX_LENGTH 1024

//directory.h   getDir >> getDirectory
//char* getDirectory(const char* fullPath) {
//    char* DirectoryPath = (char*)malloc(MAX_DIR);
//    if (DirectoryPath == NULL) {
//        return NULL;  // �޸� �Ҵ� ���� �� NULL ��ȯ
//    }
//
//    // strrchr �Լ��� ����Ͽ� ��ο��� ������ '/' ã��
//    const char* lastSlash = strrchr(fullPath, '/');
//    if (lastSlash == NULL || lastSlash == fullPath) {
//        free(DirectoryPath);
//        return NULL;  // '/'�� ���ų� �� ó������ �ִ� ���
//    }
//
//    // ������ '/' ���������� ���ڿ��� ����
//    int pathLength = lastSlash - fullPath;
//    strncpy(DirectoryPath, fullPath, pathLength);
//    DirectoryPath[pathLength] = '\0'; // ���ڿ� ���� ���� ���
//
//    return DirectoryPath;
//}
//cd.h�� �ִµ� directory.h��   isexitdir(�Լ���) >> FindDirectoryNode
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


//cd.h
//int ChangeDirectory(DirectoryTree* dirTree, char* dirPath) {
//    // ���� ����
//    DirectoryNode* tempNode = NULL;
//    DirectoryNode* savedNode = dirTree->current;  // ���� ���丮 ��带 �ӽ� ������ ����
//    char tempPath[MAX_DIR];
//    char* command = NULL;
//
//    // ���� ���丮 ('.')�� ���: �ƹ� �۾��� ���� ����
//    if (strcmp(dirPath, ".") == 0) {
//        return 0;
//    }
//
//    // ���� ���丮�� �̵��ϴ� ��� ('..')
//    if (strcmp(dirPath, "..") == 0) {
//        if (dirTree->current != dirTree->root) { // ���� ���丮�� ��Ʈ ���丮�� �ƴϸ� ���� ���丮�� �̵�
//            dirTree->current = dirTree->current->Parent;
//        }
//        return 0;
//    }
//
//    // ��θ� tempPath�� ����
//    strncpy(tempPath, dirPath, MAX_DIR - 1); // ���ڿ� ����
//    tempPath[MAX_DIR - 1] = '\0';
//
//    // �ֻ��� ���丮�� ���
//    if (strcmp(dirPath, "/") == 0) {
//        dirTree->current = dirTree->root; // ���� ���丮 = ��Ʈ ���丮
//        return 0;
//    }
//
//    // ���� ����� ���
//    if (dirPath[0] == '/') {
//        dirTree->current = dirTree->root; // ���� ���丮 = ��Ʈ ���丮
//        command = strtok(tempPath + 1, "/"); // ù��° ���丮 �̸� ����
//    }
//    else {  // ��� ����� ���
//        command = strtok(tempPath, "/"); // ù��° ���丮 �̸� ����
//    }
//
//    // ��θ� �ϳ��� Ž���ϸ� �̵�
//    while (command != NULL) {
//        // ���� ���丮�� �̵��ϴ� ���
//        tempNode = FindDirectoryNode(dirTree, command, 'd');// �ش� �̸��� ���丮�� �����ϸ� �̵�
//        if (tempNode != NULL) {
//            dirTree->current = tempNode;
//        }
//        else {
//            // ���丮�� �������� ���� ���
//            dirTree->current = savedNode; // ���� ���丮 ����
//            return -1;
//        }
//        command = strtok(NULL, "/");
//    }
//
//    return 0;
//}


//directory.h (������, �ణ�� ����) �Լ��� ReadDir���� ����
int ReadDirectory(DirectoryTree* dirTree, char* line, char* dirName)
{
    char* str; // ���ڿ� ������
    char firstSegment[MAX_NAME]; // ù��° segment�� ������ ����
    char found = 0;


    str = strtok(line, " "); // ���ڿ��� ���� ������ �и�
    if (str != NULL) {
        strncpy(firstSegment, str, MAX_NAME);
        firstSegment[MAX_NAME - 1] = '\0'; // ������ ���Ḧ ���� �� ���� �߰�
    }

    for (int count = 0; count < 10; count++) {  // 10�� �ݺ�
        str = strtok(NULL, " "); // ���� ���ڿ� �и�
    }
    //������ ���ڿ��� �ش��ϴ� �κп� ����
    if (str != NULL) { // ���ڿ��� ���� �ִ� ���
        str[strlen(str) - 1] = '\0'; // ���ڿ� ���� NULL �߰�, ���ڿ� ����, ���๮������ 
        char* found = strstr(str, dirName);// ��ҹ��� ���� ���� ���ڿ� �˻�, ��ġ�ϴ� �κ� ���ڿ��� �����ּ� ����
        if (found) { // dirName�� ��ġ�ϴ� ���ڿ��� ã�� ���
            if (strcmp(str, "/") == 0) {
                printf("/%s\n", firstSegment); // ��Ʈ ���丮�� ��� ��� ���
            }
            else {
                printf("%s/%s\n", found, firstSegment);  //��Ʈ ���丮�� �ƴѰ��, found�� firstSegment ����, ��� ���
            }
        }
    }
    return 0;
}

//directory.h (������, �ణ�� ����) �Լ��� FindDir���� ����
void FindDirectory(DirectoryTree* dirTree, char* dirName)     //Directory.txt ������ ���� ������ ���丮 �̸��� �˻�
{
    FILE* file = fopen("Directory.txt", "r"); //directory.txt ������ �б���� ����
    if (!file) {
        perror("No such file or directory");
        return;
    }
    char line[MAX_LENGTH]; //���Ͽ��� ���� �� ���� ������ �ӽ� ���� 
    while (fgets(line, sizeof(line), file)) { //������ �� �پ� �а� line�� ����, ReadDirectory�� ȣ���Ͽ� �� line���� ���丮 �̸��� �˻��ϰ� ��ġ�ϴ� ��� ���
        ReadDirectory(dirTree, line, dirName);
    }
    fclose(file);
}


// 1) ��ɾ '/'�� ���Ե��� ���� ���, ��ġ�� ���� ���丮���� �����̳� ���丮 �˻�
// 2) ��ɾ '/'�� ���ԵǾ� �ִ� ���, �����̳� ���丮 �˻�
// 2-1) ��ΰ� �߸����� ���,
// 2-2) ��ΰ� �ùٸ���, �����̳� ���丮�� �������
void* FindThread(void* arg) {
    ThreadTree* threadTree = (ThreadTree*)arg; // ������ ������ ����� �����ϴ� ����ü
    DirectoryTree* dirTree = threadTree->threadTree; // ���丮 Ʈ�� ����
    char* cmd = threadTree->command; // ������ ���
    char fullPath[MAX_DIR]; // ��ü ��θ� ������ ����
    char* fileName; // ���� �̸�
    char* dirPath; // ���丮 ���
    int dirCheck; // ���丮 ���� ���� ���� Ȯ��
    DirectoryNode* currentNode = dirTree->current;
    strncpy(fullPath, cmd, MAX_DIR); // ��ɾ�� ��ü ��� ����
    fullPath[MAX_DIR - 1] = '\0'; // �� ���� ���� ����

    // ���� �̸��� ���丮 ��� �и�
    fileName = strrchr(fullPath, '/');
    if (fileName) {
        fileName++; // '/' ���� ���ڷ� ���� �̸� ����
        dirPath = fullPath;
        *(fileName - 1) = '\0'; // ���� �̸� �տ��� ���ڿ� ����� ���丮 ��� ����
    }
    else {
        fileName = fullPath; // '/'�� ���� ���, ��ü ����� ���� �̸�
        dirPath = ".";
    }

    // �ʿ��� ��� ���丮 ����
    if (strcmp(dirPath, ".") != 0) {
        dirCheck = ChangeDirectory(dirTree, dirPath);
        if (dirCheck != 0) {
            printf("find: '%s': No such file or directory.\n", dirPath);
            dirTree->current = currentNode;
            pthread_exit(NULL);
        }
    }

    // ���� �Ǵ� ���丮 ���� ���� Ȯ��
    if (!FindDirectoryNode(dirTree, fileName, 'd') && !FindDirectoryNode(dirTree, fileName, 'f')) {
        printf("find: '%s': No such file or directory.\n", fileName);
        dirTree->current = currentNode;
        pthread_exit(NULL);
    }

    printf("%s\n", cmd); // �˻� ��� ���
    FindDirectory(dirTree, cmd);
    pthread_exit(NULL);

}
int find(DirectoryTree* dirTree, char* cmd)
{
    char* command; //��ɾ� ���� ������ 
    pthread_t ThreadArr[MAX_THREAD]; //thread �ĺ��� �迭
    ThreadTree ThreadTree[MAX_THREAD]; // thread�� �۾� ���� �迭 / threadtree ����ü �迭

    int ThreadCount = 0; // ������ thread ��
    //find . and find and find -- �� ���, ���� ���丮���� SearchDirȣ��
    if (cmd == NULL || strcmp(cmd, ".") == 0 || strcmp(cmd, "--") == 0) {
        FindDirectory(dirTree, dirTree->current->name); //���� ���丮 �˻�
        return 0;
    }
    else if (cmd[0] == '-') { //��ɾ ���(-)�� �����ϸ�(�ɼ��� ���)
        if (strcmp(cmd, "--help") == 0) {//, ��ɾ --help���� Ȯ���ϰ� ������ �ɼǿ� ���� ������ ���
            printf("Usage: find [OPTION] [path...] [expression]\n\n");
            printf("    Search for files in a directory hierarchy.\n\n");
            printf("    Options:\n");
            printf("       .         Search for files in the current directory\n");
            printf("       --        Search for files in the current directory\n");
            printf("       --help    display this help and exit\n");
            printf("default path is the current directory; default expression is -print\n");

            return -1;
        }
        else {  //��ȿ���� ���� �ɼ��� ��� �����޼����� ���� ���
            char* invalid_option = strchr(cmd, '-');
            printf("find: unknown predicate '%s'\n", invalid_option);  // ���� �޽���
            printf("Try 'find --help' for more information.\n");  // ���� �ȳ�
            return -1;
        }
    }
    else //threadTree �迭�� �ݺ��ϸ�, �� ��ɾ ���� ���ο� �����带 �����ϰ�(pthread_create), �� �����尡 �Ϸ�� ������ ��ٸ�(pthread_join).
    {
        command = strtok(cmd, " "); //cmd���� ù ��° ��ɾ� �и�
        ThreadTree[ThreadCount].threadTree = dirTree; // ���� ���丮 Ʈ�� ����
        ThreadTree[ThreadCount++].command = cmd; //ù ��° ��ɾ� ����
    }
    while (command != NULL) {   // ��ɾ �����ִ� ���� �ݺ� ( //��Ƽ������ �۾��� ���� �����̸����� ������迭�ȿ� ������ ����)
        ThreadTree[ThreadCount].threadTree = dirTree; // ���� ���丮 Ʈ�� ����
        ThreadTree[ThreadCount++].command = command; // ��ɾ� ����
        command = strtok(NULL, " "); // ���� ��ɾ� �и�
    }
    for (int i = 0; i < ThreadCount; i++) { // ��� �����带 ����
        pthread_create(&ThreadArr[i], NULL, FindThread, (void*)&ThreadTree[i]);
    }
    for (int i = 0; i < ThreadCount; i++) { // ��� �����尡 ����� ������ ��ٸ�
        pthread_join(ThreadArr[i], NULL);
    }

    return 0;


}