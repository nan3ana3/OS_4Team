#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"

void PrintLs(DirectoryNode* current);
void PrintLsA(DirectoryNode* current);
void PrintLsL(DirectoryNode* current);
void PrintLsAL(DirectoryNode* current);
extern char* instr[20];

void ls(int arc, DirectoryTree* tree) {
    char op;
    extern int optind;
    int loption = 0;
    int aoption = 0;
    DirectoryNode* current = tree->current;
    char curDir[256] = "";

    while ((op = getopt(arc, instr, "la")) != -1) {
        switch (op) {
            case 'l':
                loption = 1;
                break;
            case 'a':
                aoption = 1;
                break;
            case '?':
                return;
            default:
                printf("Error: please try again\n");
                return;
        }
    }

    if ((loption == 0) && (aoption == 0)) {
        if (instr[optind] == NULL) {
            PrintLs(current);
        } else {
            for (int i = optind; instr[i] != NULL; i++) {
                printf("\n%s : \n", instr[i]);
                DirectoryNode* target = findDirectoryNode(tree->root, instr[i]);
                if (target == NULL) {
                    perror("Error: ");
                } else {
                    PrintLs(target);
                }
            }
        }
    } else if (loption && aoption) {
        if (instr[optind] == NULL) {
            PrintLsAL(current);
        } else {
            for (int i = optind; instr[i] != NULL; i++) {
                printf("\n%s : \n", instr[i]);
                DirectoryNode* target = findDirectoryNode(tree->root, instr[i]);
                if (target == NULL) {
                    perror("Error: ");
                } else {
                    PrintLsAL(target);
                }
            }
        }
    } else if (loption) {
        if (instr[optind] == NULL) {
            PrintLsL(current);
        } else {
            for (int i = optind; instr[i] != NULL; i++) {
                printf("\n%s : \n", instr[i]);
                DirectoryNode* target = findDirectoryNode(tree->root, instr[i]);
                if (target == NULL) {
                    perror("Error: ");
                } else {
                    PrintLsL(target);
                }
            }
        }
    } else if (aoption) {
        if (instr[optind] == NULL) {
            PrintLsA(current);
        } else {
            for (int i = optind; instr[i] != NULL; i++) {
                printf("\n%s : \n", instr[i]);
                DirectoryNode* target = findDirectoryNode(tree->root, instr[i]);
                if (target == NULL) {
                    perror("Error: ");
                } else {
                    PrintLsA(target);
                }
            }
        }
    }
}

DirectoryNode* findDirectoryNode(DirectoryNode* root, const char* name) {
    if (strcmp(root->name, name) == 0) {
        return root;
    }

    DirectoryNode* child = root->LeftChild;
    while (child != NULL) {
        DirectoryNode* result = findDirectoryNode(child, name);
        if (result != NULL) {
            return result;
        }
        child = child->RightSibling;
    }
    return NULL;
}