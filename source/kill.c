////os 24 kill
#include "../include/main.h"

void kill_command(int arg) {

	//kill이 실행되면 옵션을 나누는것 하기
	char input[100];
	char* tokens[3];
	int token_count = 0;
	char* next_token;
	printf("Enter the command:\n");

	fgets(input, sizeof(input), stdin);

	size_t len = strlen(input);
	if (len > 0 && input[len - 1] == '\n') {
		input[len - 1] = '\0';
	}

	char* token = strtok_r(input, " ", &next_token);
	while (token != NULL && token_count < 3) {
		tokens[token_count++] = token;
		token = strtok_r(NULL, " ", &next_token);
	}
	//tokens[]배열에 띄어쓰기를 기준으로 하나씩 들어가 있도록 한다.

	//옵션에 따른 방법
	if (strcmp(tokens[1], "-l") == 0) {
		//kill -l은 지원하는 시그널의 목록을 나열한다.
		printf("1) SIGHUP	");
		printf("2) SIGKINT	");
		printf("3) SIGQUIT	");
		printf("4) SIGILL	\n");
		printf("5) SIGTRAP	");
		printf("6) SIGABRT	");
		printf("7) SIGBUS	");
		printf("8) SIGFPE	");
		printf("9) SIGKILL	");
	}

	else {
		int signal_number = atoi(tokens[1]);
		int pid = atoi(tokens[2]);

		if (kill(pid, 0) == -1) {
			perror("Process does not exist\n");
		}

		else {
			if (kill(pid, signal_number) == -1) {
				perror("Failed to send signal\n");
				return 1;
			}

			else {
				printf("Signal %d sent to process %d\n", signal_number, pid);
			}
		}
		
	}

	return 0;
}
