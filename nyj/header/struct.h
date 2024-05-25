#ifndef STRUCT_H
#define STRUCT_H
#define MAX_NAME 20

typedef struct UserNode //user ����
{
    char name[MAX_NAME];
    int UserID;
    int GroupID;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    struct UserNode* link;
}UserNode;

typedef struct User { //user ����
    int topUID;
    int topGID;
    UserNode* head;
    UserNode* tail;
    UserNode* current;
}UserList;

typedef struct DirectoryNode { //directory ����
    char name[MAX_NAME];
    char type;
    int mode;
    int permission[9];
    int SIZE;
    int UserID;
    int GroupID;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    struct DirectoryNode* Parent;
    struct DirectoryNode* LeftChild;
    struct DirectoryNode* RightSibling;
}DirectoryNode;

//directory ������ ��Ÿ���� Tree ���� 

typedef struct DirectoryTree { // ��Ʈ ���, ���� ��ġ�� ����Ű�� pointer 
    DirectoryNode* root;
    DirectoryNode* current;
}DirectoryTree;

//multi threading�� ���� tree 
typedef struct ThreadTree {
    DirectoryTree* threadTree;
    DirectoryTree* name;
    char* command;
    char* username;
    int mode;
    int option;
    char* content;
} ThreadTree;

/*
//stack using linked list
typedef struct StackNode {
    char name[MAX_NAME];
    struct tagStackNode* LinkNode;
}StackNode;

typedef struct Stack {
    StackNode* TopNode;
    int cnt;
}Stack;

*/
#endif

