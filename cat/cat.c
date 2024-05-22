//24 OS cat
#define _CRT_SECURE_NO_WARNINGS
#include "cat.h"


char current_directory[MAX_NAME] = "/home/user";

// ���丮 Ʈ�� �ʱ�ȭ �Լ�
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
	//pwd�� ���� ���丮�� ��ġ�� �ľ�
	printf("��ɾ� �Է�\n");
	
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

	// cat > [filename]�� ���
	if (strcmp(tokens[1] ,">")==0) {
		// �����ϳ��� �����ϰ� ctrl+D�� �Է��ϱ� ������ ���Ͽ� ���� �� �Է¹���

		// ���� ���� ��ġ�� �˾ƾ� �ϱ⿡ ����ü �̿��ϴ� ������ �����ϱ�


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
				printf("�Է��ϼ���\n");
				while ((word = getchar()) != EOF) {
					fputc(word, newfile);
				}
				fclose(newfile);
			}
		}
	}
	
	// cat -n [filename]�� ���
	else if (strcmp(tokens[1], "-n") == 0) {
		// ���Ͽ� �ٹ�ȣ�� ���ؼ� ���
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

	//token[1]�� �ش��ϴ� �κ��� ���ڿ�(�����̸�)�� ���
	// ������ ������ �����ϴ� ��� ������� ����ϴ°� �߰��ϱ�(while������ null�� ������ ������ ����)
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