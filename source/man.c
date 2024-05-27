#include "../include/main.h"

void man(char* cmd) {
    printf("-------------------------------------------------------------\n");
   // if (strcmp((*argv)[0], "man") == 0) { 
        if (cmd == NULL) { // 명령어 입력 x
            printf("What manual page do you want?\n");
            printf("For example, try 'man man'\n");
        }
        else {
            if (strcasecmp(cmd, "cd") == 0) { // cd
                printf("cd - change directory\n");
                printf("Change the shell working diectory. cd is not a command, it's "
                    "built into your shell.\n\n");
                printf("cd [-L|[-P [-e]] [-@]] [dir]\n");
                printf("-L\tforce symbolic links to be followed: resolve symbolic "
                    "links in DIR after processing instances of '..'\n");
            }
            else if (strcasecmp(cmd, "mkdir") == 0) { // mkdir
                printf("mkdir - make directories\n");
                printf("Create the DIRECTORY(ies), if they do not already exist.\n\n");
                printf("mkdir [OPTION]... DIRECTORY...\n");
                printf("-m, --mode\n");
                printf("\tset file mode (as in chmod), not a=rwx - umask\n");
                printf("-p, --parents\n");
                printf("\tno error if existing, make parent directories as needed\n");
            }
            else if (strcasecmp(cmd, "ls") == 0) { // ls
                printf("ls - list directory contents\n");
                printf("List information about the FILEs (the current directory by "
                    "default). Sort entries alphabetically if none of -cftuvSUX nor "
                    "--sort is specified.\n\n");
                printf("ls [OPTION]... [FILE]...\n");
                printf("-a, --all\n");
                printf("\tdo not ignore entries starting with .\n");
                printf("-l\tuse a long listing format\n");
            }
            else if (strcasecmp(cmd, "cat") == 0) { // cat
                printf("cat - concatenate files and print on the standard output\n");
                printf("Concatenate FILE(s_ to standard output.\n\n");
                printf("cat [OPTION]...[FILE]...\n");
                printf("-n, --number\n");
                printf("\tnumber all output lines\n");
            }
            else if (strcasecmp(cmd, "chown") == 0) { // chown
                printf("chown - change file owner and group\n");
                printf(
                    "chown changes the user and/or group ownership of each given file. "
                    "If only an owner is given, that user is made the owner of each "
                    "given file, and the files' group name, with no spaces between "
                    "them, the group ownership of the files is changed as well.\n\n");
                printf("chown [OPTION]...[OWNER][:[GROUP]] FILE...\n");
            }
            else if (strcasecmp(cmd, "clear") == 0) { // clear
                printf("clear - clear the terminal screen\n");
                printf("clear clears your screen if this is possible, including its "
                    "scrollback butter.\n");
            }
            else if (strcasecmp(cmd, "rm") == 0) { // rm
                printf("rm - remove files or directories\n");
                printf("rm removes each specified file. By default, it does not remove "
                    "directories.\n\n");
                printf("rm [OPTION]...[FILE]...\n");
                printf("-f, --force\n");
                printf("\tignore nonexistent files and arguments, never prompt\n");
                printf("-i\tprompt before every removal\n");
                printf("-r, --recursive\n");
                printf("\tremove directories and their contents recursively\n");
            }
            else if (strcasecmp(cmd, "find") == 0) { //find
                printf("find - search for files in a directory hierarchy\n");
                printf("find searches the directory tree rooted at each given "
                    "starting-point by evaluating the given expression from left to "
                    "right, according to the rules of precedence (see section "
                    "OPERATORS), until the outcome is known (the left hand side is "
                    "false for 'and' operations, true for 'or'), at which point "
                    "'find' moves on to the next file name.\n\n");
                printf("find [-H] [-L] [-P] [-D debugopts] [-0level] "
                    "[starting]point...] [expression]\n");
            }
            else if (strcasecmp(cmd, "pwd") == 0) { // pwd
                printf("pwd - print name of nurrent/working directory\n");
                printf("Print the full filename of the current working directory.\n\n");
                printf("pwd [OPTION]...\n");
                printf("-L, --logical\n");
                printf("\tuse PWD from environment, even if it contains symlinks");
                printf("-P, --physical\n");
                printf("\tavoid all symlinks\n");
            }
            else if (strcasecmp(cmd, "kill") == 0) { // kill
                printf("kill - send a signal to a process\n");
                printf(
                    "The default signal for kill is TERM. Alternate signals may be "
                    "specified in three ways: -9, -SIGKILL of -KILL. Negative PID "
                    "values may be used to choose whole process groups; see the PGID "
                    "column in ps command output. A PID of -1 is special; it indicates "
                    "all processes except the kill process itself and init.\n\n");
                printf("kill [options] <pid> [...]\n");
                printf("<pid> [...]\n");
                printf("\tSend signal to every <pid> listed.\n");
                printf("-s sig\tSIG is a signal name\n");
                printf("-n sig\tSIG is a signal number\n");
            }
            else if (strcasecmp(cmd, "man") == 0) { // man
                printf("man - an interface to the system reference manuals\n");
                printf(
                    "man is the system's manual pager. Each page argument given to man "
                    "is normally the name of a program, utility or function.\n\n");
                printf("man [man options] [[section] page ...] ...\n");
            }
            else {
                printf("no existing command\n"); // 없는 명령어 입력
            }
        }
   // }
    printf("-------------------------------------------------------------\n");
}