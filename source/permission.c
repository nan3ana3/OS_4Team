#include "../include/main.h"

// 박진성
int CheckPermission(const int* permissions, char pms, int index) {
    switch (pms) {
    case 'r': return permissions[index] ? 0 : -1; // 읽기 권한 확인
    case 'w': return permissions[index + 1] ? 0 : -1; // 쓰기 권한 확인
    case 'x': return permissions[index + 2] ? 0 : -1; // 실행 권한 확인
    default: return -1; // 잘못된 권한 요청
    }
}

int HasPermission(DirectoryNode* dirNode, char pms)
{
    // userList나 current 사용자가 NULL인지 확인
    if (userList == NULL || userList->current == NULL) {
        return -1; // 적절한 에러 코드 반환
    }

    // 관리자 (루트 사용자)는 모든 권한을 가짐
    if (userList->current->UserID == 0) {
        return 0;
    }
    // 소유자의 권한을 확인
    if (userList->current->UserID == dirNode->UserID) {
        return CheckPermission(dirNode->permission, pms, 0);
    }

    // 그룹의 권한을 확인
    if (userList->current->GroupID == dirNode->GroupID) {
        return CheckPermission(dirNode->permission, pms, 3);
    }

    // 기타 사용자의 권한을 확인
    return CheckPermission(dirNode->permission, pms, 6);
}

// 사용자의 권한을 확인하는 함수
//int HasPermission(DirectoryNode* dirNode, char pms)
//{
//    // 슈퍼유저(UID가 0)는 항상 모든 권한을 가집니다.
//    if(usrList->current->UserID == 0)
//        return 0;
//
//    // 사용자가 파일 소유자일 경우
//    if(usrList->current->UserID == dirNode->UserID){
//        if(pms == 'r'){ // 읽기 권한 확인
//            if(dirNode->permission[0] == 0)
//                return -1; // 읽기 권한 없음
//            else
//                return 0; // 읽기 권한 있음
//        }
//        if(pms == 'w'){ // 쓰기 권한 확인
//            if(dirNode->permission[1] == 0)
//                return -1; // 쓰기 권한 없음
//            else
//                return 0; // 쓰기 권한 있음
//        }
//        if(pms == 'x'){ // 실행 권한 확인
//            if(dirNode->permission[2] == 0)
//                return -1; // 실행 권한 없음
//            else
//                return 0; // 실행 권한 있음
//        }
//    }
//    // 사용자가 같은 그룹에 속해 있을 경우
//    else if(usrList->current->GroupID == dirNode->GroupID){
//        if(pms == 'r'){ // 읽기 권한 확인
//            if(dirNode->permission[3] == 0)
//                return -1; // 읽기 권한 없음
//            else
//                return 0; // 읽기 권한 있음
//        }
//        if(pms == 'w'){ // 쓰기 권한 확인
//            if(dirNode->permission[4] == 0)
//                return -1; // 쓰기 권한 없음
//            else
//                return 0; // 쓰기 권한 있음
//        }
//        if(pms == 'x'){ // 실행 권한 확인
//            if(dirNode->permission[5] == 0)
//                return -1; // 실행 권한 없음
//            else
//                return 0; // 실행 권한 있음
//        }
//    }
//    // 그 외의 경우(다른 사용자)
//    else{
//        if(pms == 'r'){ // 읽기 권한 확인
//            if(dirNode->permission[6] == 0)
//                return -1; // 읽기 권한 없음
//            else
//                return 0; // 읽기 권한 있음
//        }
//        if(pms == 'w'){ // 쓰기 권한 확인
//            if(dirNode->permission[7] == 0)
//                return -1; // 쓰기 권한 없음
//            else
//                return 0; // 쓰기 권한 있음
//        }
//        if(pms == 'x'){ // 실행 권한 확인
//            if(dirNode->permission[8] == 0)
//                return -1; // 실행 권한 없음
//            else
//                return 0; // 실행 권한 있음
//        }
//    }
//    return -1; // 유효하지 않은 권한 요청
//}



// 정수 형식의 권한 값을 이진수 배열로 변환하는 함수
int Atoi_permission(DirectoryNode* dirNode)
{
    char buffer[4];
    int tmp;

    // permission 배열 초기화
    for(int i=0;i<9;i++)
        dirNode->permission[i] = 0;

    // mode 값을 문자열로 변환하여 buffer에 저장
    sprintf(buffer, "%d", dirNode->mode);

    // 각 자리를 이진수로 변환하여 permission 배열에 저장
    for(int i=0;i<3;i++){
        tmp = buffer[i] - '0'; // 각 자리를 정수로 변환
        for (int j = 2 ; j >= 0 ; j--)
        {
            dirNode->permission[3*i+j] = tmp % 2;
            tmp /= 2;
        }
    }

    return 0;
}

// 디렉터리 노드의 권한을 출력하는 함수
void PrintPermission(DirectoryNode* dirNode)
{
    char rwx[4] = "rwx"; // 권한 문자

    // 각 권한 비트를 순회하며 출력
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(dirNode->permission[3*i+j] == 1)
                printf("%c", rwx[j]); // 권한이 있으면 해당 문자 출력
            else
                printf("-"); // 권한이 없으면 '-' 출력
        }
    }
}


