////os 24 kill
#include "../include/main.h"


// kill �Լ� ����
void kill_command(char* command, char* pid_str) {
    // �ɼǿ� ���� ó��
   
    if (strcmp(command, "-l") == 0) {
        //kill -l�� �����ϴ� �ñ׳��� ����� ����
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
    
        // ���μ��� ���� ���� Ȯ��
      if (kill(pid, 0) == -1) {
            perror("Process does not exist\n");
        } 
      else {
            // �ñ׳� ������
            if (kill(pid, signal_number) == -1) {
                perror("Failed to send signal\n");
                exit(1);
            } else {
                printf("Signal %d sent to process %d\n", signal_number, pid);
            }
        }
    }

