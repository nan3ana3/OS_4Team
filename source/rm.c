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

//// 함수 선언
//void confirm_file(const char* filename);
//void delete_file(const char* filename);
//void confirm_directory(const char* filename);
//void delete_directory(const char* dirPath);
//void rmfunc(DirectoryTree* tree, int r, int i, int f, const char* paths);
//void rm(DirectoryTree* tree, const char* command, const char* paths);

// 파일 삭제 함수
void delete_file(const char* filename) { remove(filename); }

// 디렉토리 내 모든 파일 및 하위 디렉토리를 재귀적으로 삭제
void delete_directory(const char* dirPath) {
    DIR* dir = opendir(dirPath);
    if (dir == NULL) { // 안열리면
        perror("Failed to open directory");
        return;
    }

    struct dirent* entry;
    char path[1024];
    while ((entry = readdir(dir)) != NULL) {
        // '.'와 '..'를 건너뛴다(자신 or 한단계 위 디렉토리)
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", dirPath, entry->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == 0) {  // 정상적으로 파일 정보 조회
            if (S_ISDIR(statbuf.st_mode)) { // 파일 종류 & 접근 권한
                delete_directory(path); // 하위 디렉토리인 경우 재귀적으로 삭제
            }
            else {
                delete_file(path); // 파일인 경우 삭제
            }
        }
        else {
            fprintf(stderr, "cannot remove '%s': ", path);
            perror(NULL);
        }
    }

    closedir(dir);

    // 최종적으로 디렉토리 삭제
    if (rmdir(dirPath) == 0) { //정상
        printf("Deleted directory: %s\n", dirPath);
    }
    else {
        perror("Failed to delete directory");
    }
}

// 디렉토리 내 모든 파일 및 하위 디렉토리 삭제여부 물으면서 삭제하는 함수
void confirm_directory(const char* dirPath) {
    DIR* dir = opendir(dirPath);
    if (dir == NULL) { // 안열리면
        perror("Failed to open directory");
        return;
    }

    struct dirent* entry;
    char path[1024];
    while ((entry = readdir(dir)) != NULL) {
        // '.'와 '..'를 건너뛴다(자신 or 한단계 위 디렉토리)
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", dirPath, entry->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == 0) {  //정상적으로 파일 정보 조회
            if (S_ISDIR(statbuf.st_mode)) { // 파일 종류 & 접근 권한
                confirm_directory(path); // 하위 디렉토리인 경우 재귀적으로 삭제여부확인
            }
            else {
                confirm_file(path); // 파일인 경우 삭제여부확인
            }
        }
        else {
            fprintf(stderr, "cannot remove '%s': ", path);
            perror(NULL);
        }
    }

    closedir(dir);

    // 최종적으로 디렉토리 삭제여부 확인
    char confirm;
    printf("remove directory '%s'? ", dirPath);
    scanf(" %c", &confirm);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; //입력버퍼를 비워줌
    if (confirm == 'y' || confirm == 'Y') {
        if (rmdir(dirPath) == 0) { //정상
            printf("Deleted directory: %s\n", dirPath);
        }
        else {
            perror("Failed to delete directory");
        }
    }
}

// 파일 삭제여부 묻는 함수 정의
void confirm_file(const char* filename) {
    char confirm;
    printf("remove file '%s'?: ", filename);
    scanf(" %c", &confirm);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; //입력버퍼를 비워줌
    if (confirm == 'y' || confirm == 'Y') {
        remove(filename);
    }
}

// rm 명령어 구현
void rmfunc(DirectoryTree* tree, int r, int i, int f, const char* paths) {
    char* token;
    char files[1024];
    strcpy(files, paths); // 입력된 파일 경로 목록을 복사

    // 파일 경로를 공백으로 구분하여 토큰화
    token = strtok(files, " ");
    while (token != NULL) {
        // 앞뒤 공백 제거
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

        // 다음 파일 경로로 이동
        token = strtok(NULL, " ");
    }
}

// rmfunc 함수 정의
void rm(DirectoryTree* tree, const char* command, const char* paths) {
    if (strlen(paths) > 0) {
        if (strncmp(paths, "-rif ", 5) == 0 || strncmp(paths, "-rfi ", 5) == 0 ||
            strncmp(paths, "-fri ", 5) == 0 || strncmp(paths, "-fir ", 5) == 0 ||
            strncmp(paths, "-irf ", 5) == 0 || strncmp(paths, "-ifr ", 5) == 0) {
            rmfunc(tree, 1, 1, 1, paths + 5);
        }
        else if (strncmp(paths, "-rf ", 4) == 0 ||
            strncmp(paths, "-fr ", 4) == 0) {
            // -r과 -f 옵션이 모두 포함된 경우
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
            // -f 옵션
            rmfunc(tree, 0, 0, 1, paths + 3);
        }
        else if (strncmp(paths, "-r ", 3) == 0) {
            // -r 옵션
            rmfunc(tree, 1, 0, 0, paths + 3);
        }
        else if (strncmp(paths, "-i ", 3) == 0) {
            // -i 옵션
            rmfunc(tree, 0, 1, 0, paths + 3);
        }
        else {
            // 일반 파일 삭제
            rmfunc(tree, 0, 0, 0, paths);
        }
    }
    else {
        printf("No files or directories specified for deletion or listing.\n");
    }
}