#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#ifndef MAIN_H_
#define MAIN_H_
#define DEFAULT printf("%c[%dm", 0x1B, 0)
#define BOLD printf("%c[%dm", 0x1B, 1)
#define WHITE printf("\x1b[37m")
#define BLUE printf("\x1b[34m")
#define GREEN printf("\x1b[32m")

#define MAX_BUFFER 512
#define MAX_LENGTH 200
#define MAX_DIR 50
#define MAX_NAME 20
#define MAX_THREAD 50


//User 관련 정보 저장 구조체
typedef struct UserNode
{
    char name[MAX_NAME];
    char dir[MAX_DIR];
    int UserID;
    int GroupID;
    int year;
    int month;
    int wday;
    int day;
    int hour;
    int minute;
    int sec;
    struct UserNode* link;
}UserNode;

// typedef struct tagUserNode{
//     char name[MAX_NAME];
//     char dir[MAX_DIR];
//     int UID;
//     int GID;
//     int year;
//     int month;
//     int wday;
//     int day;
//     int hour;
//     int minute;
//     int sec;
//     struct tagUserNode* LinkNode;
// }UserNode;



//UserNode를 추적할 수 있는 구조체
typedef struct User {
    int topUID;
    int topGID;
    UserNode* head;
    UserNode* tail;
    UserNode* current;
}UserList;

// typedef struct tagUser{
//     int topUID;
//     int topGID;
//     UserNode* head;
//     UserNode* tail;
//     UserNode* current;
// }UserList;


// Directory 트리 노드
// 디렉토리이면 d타입, File 이면 f타입
typedef struct DirectoryNode {
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

// typedef struct tagDirectoryNode{
//     char name[MAX_NAME];
//     char type;
//     int mode;
//     int permission[9];
//     int SIZE;
//     int UID;
// 	int GID;
// 	int month;
//     int day;
//     int hour;
//     int minute;
// 	struct tagDirectoryNode* Parent;
// 	struct tagDirectoryNode* LeftChild;
// 	struct tagDirectoryNode* RightSibling;
// }DirectoryNode;

// 디렉토리 tree를 나타내고 추적할 수 있는 구조체
typedef struct DirectoryTree {
    DirectoryNode* root;
    DirectoryNode* current;
}DirectoryTree;

// typedef struct tagDirectoryTree{
// 	DirectoryNode* root;
// 	DirectoryNode* current;
// }DirectoryTree;


//stack using linked list
typedef struct tagStackNode{
	char name[MAX_NAME];
	struct tagStackNode* LinkNode;
}StackNode;

typedef struct tagStack{
	StackNode* TopNode;
	int cnt;
}Stack;

//multi threading tree 
typedef struct ThreadTree {
    DirectoryTree* threadTree;
    DirectoryTree* name;
    char* command;
    char* username;
    int mode;
    int option;
    char* content;
} ThreadTree;


// typedef struct threadTree {
//     DirectoryTree *threadTree;
//     DirectoryTree *name;
//     char *cmd;
//     char *username;
//     int mode;
//     int option;
//     char *content;
// } ThreadTree;

//time
time_t ltime;
struct tm *today;

//mkdir.c
int mkdir_command(DirectoryTree* dirTree, char* cmd);
int MakeDir(DirectoryTree* dirTree, char* dirName, char type);
void *mkdir_thread(void *arg);

// 유연우
// //rm.c
void confirm_file(const char* filename);
void delete_file(const char* filename);
void confirm_directory(const char* filename);
void delete_directory(const char* dirPath);
void rmfunc(DirectoryTree* tree, int r, int i, int f, const char* paths);
void rm(DirectoryTree* tree, const char* command, const char* paths);
// int rm(DirectoryTree* dirTree, char* cmd);
// int RemoveDir(DirectoryTree* dirTree, char* dirName);
// void *rm_thread(void *arg);

// man.c
void man(char* cmd);

// 박진성
// //cd.c
DirectoryNode* FindDirectoryNode(DirectoryTree* dirTree, char* dirName, char type);
int ChangeDirectory(DirectoryTree* dirTree, char* dirPath);
char* PrintDirectoryPath(DirectoryTree* dirTree);
int cd(DirectoryTree* dirTree, char* cmd);

// int cd(DirectoryTree* dirTree, char* cmd);
// int Movecurrent(DirectoryTree* dirTree, char* dirPath);
// int MovePath(DirectoryTree* dirTree, char* dirPath);

// //pwd.c : 박진성
// void PrintDirectoryPath(DirectoryTree* dirTree);
void pwd(DirectoryTree* dirTree, char* cmd);

// int pwd(DirectoryTree* dirTree, Stack* dirStack, char* cmd);
// int PrintPath(DirectoryTree* dirTree, Stack* dirStack);

//ls.c
int ls(DirectoryTree* dirTree, char* cmd);
int ListDir(DirectoryTree* dirTree, int option);
void* ls_thread(void *arg);

// //cat.c
void init_directory_tree(DirectoryTree* dirTree);
void cat(DirectoryTree* dirTree, const char* cmd);

// kill.c
void kill_command(int arg);

// int cat(DirectoryTree* dirTree, char* cmd);
// int cat_print(DirectoryTree* dirTree, char* fName, int o);
// void *cat_thread(void *arg);

// //chmod.c
// int chmod(DirectoryTree* dirTree, char* cmd);
// int ChangeMode(DirectoryTree* dirTree, int mode, char* dirName);
// void *chmod_thread(void *arg);

// //chown.c
void chown_command(DirectoryTree* dirtree, char* cmd);
void MoveDir(DirectoryTree* dirtree, const char* srcPath, const char* destPath);
void UncompressDir(DirectoryTree* dirtree, const char* path);
// int ft_chown(DirectoryTree* dirTree, char* cmd);
// int ChangeOwner(DirectoryTree* dirTree, char* userName, char* dirName, int flag);
// void *chown_thread(void *arg);

// //find.c : 박진성
void* FindThread(void* arg);
int find(DirectoryTree* dirTree, char* cmd);
int ReadDirectory(DirectoryTree* dirTree, char* line, char* dirName);
void FindDirectory(DirectoryTree* dirTree, char* dirName);
// int find(DirectoryTree* dirTree, char* cmd);
// int ReadDir(DirectoryTree* dirTree, char* tmp, char* dirName);
// void FindDir(DirectoryTree* dirTree, char* dirName);
// void *find_thread(void *arg);


// //grep.c
// int grep_print(DirectoryTree* dirTree, char *search, char* fName, int o);
// void *grep_thread(void *arg);
// int grep(DirectoryTree* dirTree, char* cmd);

//utility.c
void DestroyNode(DirectoryNode* dirNode);
void getPath(DirectoryTree* dirTree, DirectoryNode* dirNode, Stack* dirStack);
void WriteNode(DirectoryTree* dirTree, DirectoryNode* dirNode, Stack* dirStack);
int ReadNode(DirectoryTree* dirTree, char* tmp);
void GetMonth(int i);
void GetWeek(int i);
void Instruction(DirectoryTree* dirTree, char* cmd);
void Start();
void PrintHead(DirectoryTree* dirTree, Stack* dirStack);

//permission.c
int HasPermission(DirectoryNode* dirNode, char o);
int Atoi_permission(DirectoryNode* dirNode);
void PrintPermission(DirectoryNode* dirNode);
int CheckPermission(const int* permissions, char pms, int index); //박진성

//directory.c
//진성
void DestroyDir(DirectoryNode* dirNode);
DirectoryNode* FindDirectoryNode(DirectoryTree* dirTree, char* dirName, char type);
char* getDirectory(const char* fullPath);

//void DestroyDir(DirectoryNode* dirNode);
//DirectoryNode* IsExistDir(DirectoryTree* dirTree, char* dirName, char type);
//char* getDir(char* dirPath);
void SaveDir(DirectoryTree* dirTree, Stack* dirStack);
DirectoryTree* LoadDir();



//user.c
UserList* InitializeUser();
void WriteUser(UserList* userList, UserNode* userNode);
void SaveUserList(UserList* userList);
int ReadUser(UserList* userList, char* tmp);
UserList* LoadUserList();
UserNode* IsExistUser(UserList* userList, char* userName);
char* GetUID(DirectoryNode* dirNode);
char* GetGID(DirectoryNode* dirNode);
void Login(UserList* userList, DirectoryTree* dirTree);

//stack.c
int IsEmpty(Stack* dirStack);
Stack* InitializeStack();
int Push(Stack* dirStack, char* dirName);
char* Pop(Stack* dirStack);

//global variable
DirectoryTree* Linux;
Stack* dStack;
UserList* userList;
FILE* Directory; //경로문자열
FILE* User;

#endif // MAIN_H_
