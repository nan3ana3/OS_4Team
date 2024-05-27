//#define _CRT_SECURE_NO_WARNINGS
//#include "struct.h"
//#include <dirent.h>
//#include <errno.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/stat.h>
//#include <unistd.h>
#include "../include/main.h"

//// �Լ� ����
//void confirm_file(const char* filename);
//void delete_file(const char* filename);
//void confirm_directory(const char* filename);
//void delete_directory(const char* dirPath);
//void rmfunc(DirectoryTree* tree, int r, int i, int f, const char* paths);
//void rm(DirectoryTree* tree, const char* command, const char* paths);

// ���� ���� �Լ�
void delete_file(const char* filename) { remove(filename); }

// ���丮 �� ��� ���� �� ���� ���丮�� ��������� ����
void delete_directory(const char* dirPath) {
    DIR* dir = opendir(dirPath);
    if (dir == NULL) { // �ȿ�����
        perror("Failed to open directory");
        return;
    }

    struct dirent* entry;
    char path[1024];
    while ((entry = readdir(dir)) != NULL) {
        // '.'�� '..'�� �ǳʶڴ�(�ڽ� or �Ѵܰ� �� ���丮)
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", dirPath, entry->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == 0) {  // ���������� ���� ���� ��ȸ
            if (S_ISDIR(statbuf.st_mode)) { // ���� ���� & ���� ����
                delete_directory(path); // ���� ���丮�� ��� ��������� ����
            }
            else {
                delete_file(path); // ������ ��� ����
            }
        }
        else {
            fprintf(stderr, "cannot remove '%s': ", path);
            perror(NULL);
        }
    }

    closedir(dir);

    // ���������� ���丮 ����
    if (rmdir(dirPath) == 0) { //����
        printf("Deleted directory: %s\n", dirPath);
    }
    else {
        perror("Failed to delete directory");
    }
}

// ���丮 �� ��� ���� �� ���� ���丮 �������� �����鼭 �����ϴ� �Լ�
void confirm_directory(const char* dirPath) {
    DIR* dir = opendir(dirPath);
    if (dir == NULL) { // �ȿ�����
        perror("Failed to open directory");
        return;
    }

    struct dirent* entry;
    char path[1024];
    while ((entry = readdir(dir)) != NULL) {
        // '.'�� '..'�� �ǳʶڴ�(�ڽ� or �Ѵܰ� �� ���丮)
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", dirPath, entry->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == 0) {  //���������� ���� ���� ��ȸ
            if (S_ISDIR(statbuf.st_mode)) { // ���� ���� & ���� ����
                confirm_directory(path); // ���� ���丮�� ��� ��������� ��������Ȯ��
            }
            else {
                confirm_file(path); // ������ ��� ��������Ȯ��
            }
        }
        else {
            fprintf(stderr, "cannot remove '%s': ", path);
            perror(NULL);
        }
    }

    closedir(dir);

    // ���������� ���丮 �������� Ȯ��
    char confirm;
    printf("remove directory '%s'? ", dirPath);
    scanf(" %c", &confirm);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; //�Է¹��۸� �����
    if (confirm == 'y' || confirm == 'Y') {
        if (rmdir(dirPath) == 0) { //����
            printf("Deleted directory: %s\n", dirPath);
        }
        else {
            perror("Failed to delete directory");
        }
    }
}

// ���� �������� ���� �Լ� ����
void confirm_file(const char* filename) {
    char confirm;
    printf("remove file '%s'?: ", filename);
    scanf(" %c", &confirm);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; //�Է¹��۸� �����
    if (confirm == 'y' || confirm == 'Y') {
        remove(filename);
    }
}

// rm ��ɾ� ����
void rmfunc(DirectoryTree* tree, int r, int i, int f, const char* paths) {
    char* token;
    char files[1024];
    strcpy(files, paths); // �Էµ� ���� ��� ����� ����

    // ���� ��θ� �������� �����Ͽ� ��ūȭ
    token = strtok(files, " ");
    while (token != NULL) {
        // �յ� ���� ����
        char* start = token;
        while (*start == ' ')
            start++;
        char* end = start + strlen(start) - 1;
        while (end > start && *end == ' ')
            end--;
        *(end + 1) = '\0';

        struct stat statbuf;
        if (stat(start, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                if (!r) {
                    printf("Cannot remove '%s': Is a directory\n", start);
                }
                else if (i & !f) {
                    confirm_directory(start);
                }
                else {
                    delete_directory(start);
                }
            }
            else {
                if (i & !f) {
                    confirm_file(start);
                }
                else {
                    delete_file(start);
                }
            }
        }
        else {
            fprintf(stderr, "cannot remove '%s': ", start);
            perror(NULL);
        }

        // ���� ���� ��η� �̵�
        token = strtok(NULL, " ");
    }
}

// rmfunc �Լ� ����
void rm(DirectoryTree* tree, const char* command, const char* paths) {
    if (strlen(paths) > 0) {
        if (strncmp(paths, "-rif ", 5) == 0 || strncmp(paths, "-rfi ", 5) == 0 ||
            strncmp(paths, "-fri ", 5) == 0 || strncmp(paths, "-fir ", 5) == 0 ||
            strncmp(paths, "-irf ", 5) == 0 || strncmp(paths, "-ifr ", 5) == 0) {
            rmfunc(tree, 1, 1, 1, paths + 5);
        }
        else if (strncmp(paths, "-rf ", 4) == 0 ||
            strncmp(paths, "-fr ", 4) == 0) {
            // -r�� -f �ɼ��� ��� ���Ե� ���
            rmfunc(tree, 1, 0, 1, paths + 4);
        }
        else if (strncmp(paths, "-ri ", 4) == 0 ||
            strncmp(paths, "-ir ", 4) == 0) {
            rmfunc(tree, 1, 1, 0, paths + 4);
        }
        else if (strncmp(paths, "-if ", 4) == 0 ||
            strncmp(paths, "-fi ", 4) == 0) {
            rmfunc(tree, 0, 1, 1, paths + 4);
        }
        else if (strncmp(paths, "-f ", 3) == 0) {
            // -f �ɼ�
            rmfunc(tree, 0, 0, 1, paths + 3);
        }
        else if (strncmp(paths, "-r ", 3) == 0) {
            // -r �ɼ�
            rmfunc(tree, 1, 0, 0, paths + 3);
        }
        else if (strncmp(paths, "-i ", 3) == 0) {
            // -i �ɼ�
            rmfunc(tree, 0, 1, 0, paths + 3);
        }
        else {
            // �Ϲ� ���� ����
            rmfunc(tree, 0, 0, 0, paths);
        }
    }
    else {
        printf("No files or directories specified for deletion or listing.\n");
    }
}