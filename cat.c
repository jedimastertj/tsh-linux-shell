#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    
    chdir(argv[argc-1]);
    FILE* file;
    char content[50];
    char ch;
    int ind = 1;
    int mode = 0;

    if (argc < 3) {
        printf("cat command failed: too few arguments \n");
        return 0;
    }

    if (strcmp(argv[1], "-n") == 0) {
        ind = 2;
        mode = 1;
    } else if (strcmp(argv[1], "-e") == 0) {
        ind = 2;
        mode = 2;
    }

    for (; ind < argc-1; ind++) {
        file = fopen(argv[ind], "r");

        if (file != NULL) {

            if (mode == 0) {
                // cat
                while (fgets(content, sizeof(content), file) != NULL) {
                    printf("%s", content);
                }
                printf("\n");

            } else if (mode == 1) {
                // cat -n
                int line = 1;
                printf("%d ", line);
                while ((ch = fgetc(file)) != EOF) {
                    printf("%c", ch);
                    if (ch == '\n') {
                        printf("%d ", ++line);
                    }
                } 
                printf("\n");

            } else if (mode == 2) {
                // cat -e
                while ((ch = fgetc(file)) != EOF) {
                    if (ch == '\n') {
                        printf("$");
                    }
                    printf("%c", ch);
                } 
                printf("$ \n");
            }

            fclose(file);

        } else {
            printf("couldn't read file: '%s' \n", argv[ind]);
        }

    }

    return 0;
}
