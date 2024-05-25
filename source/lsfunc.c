#include <sys/types.h> 
#include <dirent.h> 
#include <unistd.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <dirent.h> 
#include <grp.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct dirent* dirptr;
void rwx();
void PrintID();

typedef struct dlist
//디렉토리 안의 파일 또는 디렉토리의 내용을 위한 구조체
{
	char name[100];
	int filesize; //파일 사이즈
	int blocks; //파일의 블럭
	char passwd[10]; //파일 소유자
	char group[10]; //그룹 이름
	int nlink; //링크의 개수
	char file_mode[10]; //파일의 접근 권한 및 파일 또는 디렉토리 유형

	int year; //년 월 일 시 분 초
	int month;
	int day;
	int hour;
	int min;
	int sec;
}dlist;

void sort(dlist infoList[], int count)
//디렉토리 안의 내용을 이름 순으로 정렬해준다.
{
	int i, j;
	dlist temp;

	for (i = 0; i < count - 1; i++)
	{
		for (j = 1; j < count - i; j++)
		{
			if (strcmp(infoList[j - 1].name, infoList[j].name) > 0)
			{
				temp = infoList[j - 1];
				infoList[j - 1] = infoList[j];
				infoList[j] = temp;
			}
		}
	}
}

void PrintLs(char *buf, int count) //옵션이 없는 경우 사용하는 함수
{
	struct dirent* dirp;
	dlist infoList[count];
	int i = 0;
	DIR *dp = opendir(buf);
	while ((dirp = readdir(dp)) != NULL)
	{
		strcpy(infoList[i].name, dirp->d_name);
		i++;
	}
	sort(infoList, count);
	for (i = 0; i < count; i++)
	{
		if (infoList[i].name[0] != '.')
			printf("%s\t", infoList[i].name);
	}
	closedir(dp);
	printf("\n");
}

void PrintLsA(char *buf, char *dname, int count) //-a 옵션에서 사용하는 함수
{
	struct dirent* dirp;
	dlist  infoList[count];
	int i = 0;
	DIR *dp;
	if (dname == NULL)
		dp = opendir(".");
	else
		dp = opendir(dname);

	while ((dirp = readdir(dp)) != NULL)
	{
		strcpy(infoList[i].name, dirp->d_name);
		i++;
	}
	sort(infoList, count);

	for (i = 0; i < count; i++)
		printf("%s\t", infoList[i].name);
	printf("\n");
	closedir(dp);
}

void PrintLsL(char *buf, char *dname, int count) //-l 옵션에서 사용하는 함수
{
	DIR *dp;
	struct dirent* dirp;
	dlist  infoList[count];
	struct stat file_info;
	struct passwd *my_passwd;
	struct group *my_group;
	struct tm *tminfo;
	mode_t file_mode;
	int i = 0;
	int check;
	int sumblocks = 0;
	
	if (dname == NULL)
		dp = opendir(".");
	else 
	{
		dp = opendir(dname);
		chdir(dname);
	}

	while ((dirp = readdir(dp)) != NULL)
	{
		stat(dirp->d_name, &file_info);

		file_mode = file_info.st_mode;

		strcpy(infoList[i].name, dirp->d_name);
		rwx(infoList, i, file_mode);

		infoList[i].nlink = file_info.st_nlink;
		infoList[i].filesize = file_info.st_size;
		infoList[i].blocks = file_info.st_blocks;

		my_passwd = getpwuid(file_info.st_uid);
		my_group = getgrgid(file_info.st_gid);
		strcpy(infoList[i].passwd, my_passwd->pw_name);
		strcpy(infoList[i].group, my_group->gr_name);

		tminfo = localtime(&(file_info.st_mtime));

		infoList[i].year = tminfo->tm_year;
		infoList[i].month = tminfo->tm_mon;
		infoList[i].day = tminfo->tm_mday;
		infoList[i].hour = tminfo->tm_hour;
		infoList[i].min = tminfo->tm_min;
		infoList[i].sec = tminfo->tm_sec;

		i++;
	}

	sort(infoList, count);

	for (i = 0; i < count; i++)
	{
		if (infoList[i].name[0] != '.')
			sumblocks += infoList[i].blocks;
	}

	printf("Total : %d\n", sumblocks / 2);
	for (i = 0; i < count; i++)
	{
		if (infoList[i].name[0] != '.') //숨김 디렉토리는 넘어간다.
		{
			printf("%s  ", infoList[i].file_mode);
			printf("%3d ", infoList[i].nlink);
			printf("%s ", infoList[i].passwd);
			printf("%s  ", infoList[i].group);
			printf("%10d   ", infoList[i].filesize);
			printf("%04d-%02d-%02d  ", infoList[i].year + 1900, infoList[i].month + 1, infoList[i].day);
			printf("%02d:%02d:%02d   ", infoList[i].hour, infoList[i].min, infoList[i].sec);
			printf("%s  \n", infoList[i].name);
		}
	}
	closedir(dp);
	chdir(buf);
	printf("\n");
}

void PrintLsAL(char *buf, char *dname, int count) //-al 옵션
{
	DIR *dp; //디렉토리 포인터
	struct dirent* dirp; //디렉토리의 각종 내용을 위한 구조체 선언. 기본으로 제공된다.
	dlist infoList[count]; //위에서 직접 필요한 내용만을 위해서 만든 구조체의 선언

	struct stat file_info; //각종 디렉토리 관련 구조체들과 자료형들
	struct passwd *my_passwd;
	struct group *my_group;
	struct tm *tminfo;
	mode_t file_mode;

	int i = 0;
	int check;
	int sumblocks = 0;

	if (dname == NULL) 
	//printLsAL(buf, NULL, count)로 함수를 호출했으므로 현재 디렉토리를 open
		dp = opendir(".");
	else 
	//printLsAL(buf, vec[i], count)로 함수를 호출했으므로 vec[i] 디렉토리를 open
	{ 
		dp = opendir(dname);
		chdir(dname);
	}

	while ((dirp = readdir(dp)) != NULL)
	{
		stat(dirp->d_name, &file_info);	//stat 함수는 디렉토리 안의 내용을 file_info 구조체에 저장

		file_mode = file_info.st_mode; //파일 모드 저장

		strcpy(infoList[i].name, dirp->d_name); //각종 정보들을 필요한 내용만을 위해서 만든 구조체에 저장
		rwx(infoList, i, file_mode);

		infoList[i].nlink = file_info.st_nlink;
		infoList[i].filesize = file_info.st_size;
		infoList[i].blocks = file_info.st_blocks;

		my_passwd = getpwuid(file_info.st_uid);
		my_group = getgrgid(file_info.st_gid);
		strcpy(infoList[i].passwd, my_passwd->pw_name);
		strcpy(infoList[i].group, my_group->gr_name);

		tminfo = localtime(&(file_info.st_mtime));

		infoList[i].year = tminfo->tm_year;
		infoList[i].month = tminfo->tm_mon;
		infoList[i].day = tminfo->tm_mday;
		infoList[i].hour = tminfo->tm_hour;
		infoList[i].min = tminfo->tm_min;
		infoList[i].sec = tminfo->tm_sec;

		i++;
	}

	sort(infoList, count); //이름순 정렬

	for (i = 0; i < count; i++)
	{
		sumblocks += infoList[i].blocks;
	}

	printf("Total : %d\n", sumblocks / 2);
	for (i = 0; i < count; i++)
	{
		printf("%s  ", infoList[i].file_mode);
		printf("%3d ", infoList[i].nlink);
		printf("%s ", infoList[i].passwd);
		printf("%s  ", infoList[i].group);
		printf("%10d   ", infoList[i].filesize);
		printf("%04d-%02d-%02d  ", infoList[i].year + 1900, infoList[i].month + 1, infoList[i].day);
		printf("%02d:%02d:%02d   ", infoList[i].hour, infoList[i].min, infoList[i].sec);
		printf("%s  \n", infoList[i].name);

	}
	closedir(dp);
	chdir(buf);
	printf("\n");
}

void rwx(dlist infoList[], int i, mode_t file_mode)
//파일 접근 권한 및 파일 or 디렉토리 유형 확인을 위한 함수
{
	if (S_ISDIR(file_mode)) //디렉토리이면 d, 아니면 -
	{
		infoList[i].file_mode[0] = 'd';
	}
	else
		infoList[i].file_mode[0] = '-';

	if (file_mode & S_IRUSR) //사용자가 파일을 읽을 수 있으면 r, 아니면 -
	{
		infoList[i].file_mode[1] = 'r';
	}
	else
		infoList[i].file_mode[1] = '-';

	if (file_mode & S_IWUSR) //사용자가 파일을 쓸 수 있으면 w, 아니면 -
	{
		infoList[i].file_mode[2] = 'w';
	}
	else
		infoList[i].file_mode[2] = '-';

	if (file_mode & S_IXUSR) //사용자가 파일을 실행할 수 있으면 x, 아니면 -
	{
		infoList[i].file_mode[3] = 'x';
	}
	else
		infoList[i].file_mode[3] = '-';

	if (file_mode & S_IRGRP) //그룹이 파일을 읽을 수 있으면 r, 아니면 -
	{
		infoList[i].file_mode[4] = 'r';
	}
	else
		infoList[i].file_mode[4] = '-';

	if (file_mode & S_IWGRP) //그룹이 파일을 쓸 수 있으면 w, 아니면 -
	{
		infoList[i].file_mode[5] = 'w';
	}
	else
		infoList[i].file_mode[5] = '-';

	if (file_mode & S_IXGRP) //그룹이 파일을 실행할 수 있으면 x, 아니면 -
	{
		infoList[i].file_mode[6] = 'x';
	}
	else
		infoList[i].file_mode[6] = '-';

	if (file_mode & S_IROTH) //기타 다른 사람이 파일을 읽을 수 있으면 r, 아니면 -
	{
		infoList[i].file_mode[7] = 'r';
	}
	else
		infoList[i].file_mode[7] = '-';

	if (file_mode & S_IWOTH) //기타 다른 사람이 파일을 쓸 수 있으면 r, 아니면 -
	{
		infoList[i].file_mode[8] = 'w';
	}
	else
		infoList[i].file_mode[8] = '-';

	if (file_mode & S_IXOTH) //기타 다른 사람이 파일을 실행할 수 있으면 r, 아니면 -
	{
		infoList[i].file_mode[9] = 'x';
	}
	else
		infoList[i].file_mode[9] = '-';
	infoList[i].file_mode[10] = '\0';
}

