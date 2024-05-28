////os 24 kill
#include "../include/main.h"


// kill 함수 정의
void kill_command(char* command, char* pid_str) {
    // 옵션에 따른 처리
   
    if (strcmp(command, "-l") == 0) {
        //kill -l은 지원하는 시그널의 목록을 나열
        printf("1) SIGHUP\t");
        printf("2) SIGKINT\t");
        printf("3) SIGQUIT\t");
        printf("4) SIGILL\n");
        printf("5) SIGTRAP\t");
        printf("6) SIGABRT\t");
        printf("7) SIGBUS\t");
        printf("8) SIGFPE\t");
        printf("9) SIGKILL\n");
       
        return;
    } 
    
     
    int signal_number = atoi(command);
    int pid = atoi(pid_str);
    
        // 프로세스 존재 여부 확인
      if (kill(pid, 0) == -1) {
            perror("Process does not exist\n");
        } 
      else {
            // 시그널 보내기
            if (kill(pid, signal_number) == -1) {
                perror("Failed to send signal\n");
                exit(1);
            } else {
                printf("Signal %d sent to process %d\n", signal_number, pid);
            }
        }
    }

