#include "../include/main.h"

int main()
{
    char cmd[100];
    Linux = LoadDir();
    userList = LoadUserList();
    dStack = InitializeStack();

    Login(userList, Linux);
    Start();
    SaveUserList(userList);

    while(1){
        PrintPrompt(Linux);
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd)-1] = '\0';
        ExecuteCommand(Linux, cmd);
    }
    return 0;
}
