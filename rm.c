#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char const *argv[]) {

    chdir(argv[argc-1]);

    if (argc < 3) {
        printf("rm command failed: too few arguments \n");
        return 0;
    }

    if (strcmp(argv[1], "-i") == 0) {

        // rm -i
        for (int i = 2; i < argc-1; i++) {
            DIR* folder = opendir(argv[i]);
            if (folder != NULL) {
                printf("rm command failed: can't remove '%s' as it is a directory \n", argv[i]);
            } else if (access(argv[i], F_OK) == 0) {
                printf("rm: remove file '%s'? ", argv[i]);
                char choice = getchar(); getchar();
                if (choice == 'y' || choice == 'Y') {
                    remove(argv[i]);
                }
            } else {
                printf("rm command failed: couldn't remove file '%s' \n", argv[i]);
            }
        }

    } else if (strcmp(argv[1], "-d") == 0) {

        // rm -d
        for (int i = 2; i < argc-1; i++) {
            DIR* folder = opendir(argv[i]);
            if (folder != NULL) {
                int count = 0;
                struct dirent* file;
                while ((file = readdir(folder)) != NULL) {
                    if (file->d_name[0] != '.') {
                        count++;
                    }
                }
                if (count == 0) {
                    if (rmdir(argv[i]) != 0) {
                        printf("rm command failed: couldn't remove directory '%s' \n", argv[i]);
                    }
                } else {
                    printf("can't remove directory '%s': directory not empty \n", argv[i]);
                }

            } else {
                printf("rm command failed: couldn't remove directory '%s' \n", argv[i]);
            }
        }

    } else {
        // rm
        for (int i = 1; i < argc-1; i++) {
            DIR* folder = opendir(argv[i]);
            if (folder != NULL) {
                printf("rm command failed: can't remove '%s' as it is a directory \n", argv[i]);
            } else if (remove(argv[1]) != 0) {
                printf("rm command failed: couldn't remove file '%s' \n", argv[i]);
            }
        } 
    }


    return 0;
}
