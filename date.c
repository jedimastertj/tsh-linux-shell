#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {

    const char dformat[30] = "%A %d %B %G %I:%M:%S %p %Z";
    time_t t = time(NULL);
    struct tm* timeInfo;
    char time[64];

    if (argc == 1) {
        // date
        timeInfo = localtime(&t);
        strftime(time, sizeof(time), dformat, timeInfo);
        printf("%s \n", time);

    } else if (argc == 2) {

        if (strcmp(argv[1], "-u") == 0) {
            // date -u
            timeInfo = gmtime(&t);
            strftime(time, sizeof(time), dformat, timeInfo);
            printf("%s \n", time);

        } else {
            printf("date command failed: invalid argument(s) \n");
        }

    } else if (argc == 3) {

        if (strcmp(argv[1], "-r") == 0) {
            // date -r
            struct stat fileInfo;
            if (stat(argv[2], &fileInfo) == 0) {
                timeInfo = localtime(&fileInfo.st_mtime);
                strftime(time, sizeof(time), dformat, timeInfo);
                printf("%s \n", time);

            } else {
                printf("date command failed: couldn't get file info \n");
            }

        } else {
            printf("date command failed: invalid argument(s) \n");
        }

    } else {
        printf("date command failed: too many arguments \n");
    }

    return 0;
}
