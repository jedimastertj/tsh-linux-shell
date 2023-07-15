#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    
    chdir(argv[argc-1]);
    
    if (strcmp(argv[1], "-v") == 0 && argc == 4) {
        // mkdir -v
        if (access(argv[2], F_OK) != 0) {
            mkdir(argv[2], 0777);
            printf("mkdir: created directory '%s' \n", argv[2]);
        } else {
            printf("mkdir command failed: existing directory has same name \n");
        }

    } else if (strcmp(argv[1], "-m") == 0 && argc == 5) {
        // mkdir -m
        char permissions[5];
        strcpy(permissions, argv[2]);
        if (access(argv[3], F_OK) != 0) {
            int check = atoi(permissions);
            if (check <= 777 && check >= 0) {
                int permOct = strtol(permissions, NULL, 8);
                mkdir(argv[3], permOct);
            } else {
                printf("mkdir command failed: invalid permission code \n");
            }
        } else {
            printf("mkdir command failed: existing directory has same name \n");
        }

    } else if (argc == 3) {
        // mkdir
        if (access(argv[1], F_OK) != 0) {
            mkdir(argv[1], 0777);
        } else {
            printf("mkdir command failed: existing directory has same name \n");
        }

    } else {
        printf("mkdir command failed: invalid argument(s) \n");
    }

    return 0;
}
