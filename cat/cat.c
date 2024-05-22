//24 OS cat
#define _CRT_SECURE_NO_WARNINGS
#include "cat.h"


char current_directory[MAX_NAME] = "/home/user";

// 디렉토리 트리 초기화 함수
DirectoryTree* init_directory_tree() {
	DirectoryTree* tree = (DirectoryTree*)malloc(sizeof(DirectoryTree));
	tree->root = (DirectoryNode*)malloc(sizeof(DirectoryNode));
	strcpy(tree->root->name, "/");
	tree->root->type = 'd';
	tree->root->Parent = NULL;
	tree->root->LeftChild = NULL;
	tree->root->RightSibling = NULL;
	tree->current = tree->root;
	return tree;
}

//void cat() {
int main(){

	char option;
	char input[100];
	char* tokens[5];
	int token_count = 0;
	char* next_token;
	char word;
	int index = 0;
	//pwd로 현재 디렉토리의 위치를 파악
	printf("명령어 입력\n");
	
	fgets(input, sizeof(input), stdin);

	size_t len = strlen(input);
	if (len > 0 && input[len - 1] == '\n') {
		input[len - 1] = '\0';
	}
	
	char* token = strtok_s(input, " ",&next_token);
	while (token != NULL && token_count < 5) {
		tokens[token_count++] = token;
		token = strtok_s(NULL, " ",&next_token);
	}

	// cat > [filename]인 경우
	if (strcmp(tokens[1] ,">")==0) {
		// 파일하나를 생성하고 ctrl+D를 입력하기 전까지 파일에 넣을 것 입력받음

		// 파일 생성 위치를 알아야 하기에 구조체 이용하는 것으로 수정하기


		if (tokens[2] == NULL) {
			printf("Error: Pleas enter the filename\n");
			return 1;
		}
		else {
			FILE* newfile;
			errno_t err = fopen_s(&newfile, tokens[2], "wt");
			if (err != 0 || newfile == NULL) {
				printf("Error: failed to create the new file\n");
				return 1;
			}
			else {
				printf("입력하세요\n");
				while ((word = getchar()) != EOF) {
					fputc(word, newfile);
				}
				fclose(newfile);
			}
		}
	}
	
	// cat -n [filename]인 경우
	else if (strcmp(tokens[1], "-n") == 0) {
		// 파일에 줄번호를 더해서 출력
		FILE* file_print;
		errno_t err = fopen_s(&file_print, tokens[2], "r");
		if (err != 0 || file_print == NULL) {
			printf("Error: Filed to open the file\n");
			return 1;
		}

		int line_number = 1;
		while (fgets(input, sizeof(input), file_print)) {
			printf("%d  %s", line_number++, input);
		}
		fclose(file_print);
	}

	//token[1]에 해당하는 부분이 문자열(파일이름)인 경우
	// 파일을 여러개 나열하는 경우 순서대로 출력하는거 추가하기(while문으로 null값 만나기 전까지 진행)
	else if (strlen(tokens[1]) > 0) {
		FILE* file_print;
		errno_t err = fopen_s(&file_print, tokens[1], "r");
		if (err != 0) {
			printf("Error: Filed to open the file\n");
			return 1;
		}

		while (fgets(input, sizeof(input), file_print)) {
			printf("%s", input);
		}
		fclose(file_print);

	}

	else {
		printf("Error: Please try something else!");
		return 1;
	}

	return 0;

}