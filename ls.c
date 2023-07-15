#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char const *argv[]) {

    DIR* folder = opendir(argv[argc-1]);

    if (folder != NULL) {
        struct dirent* file;

        if (argc == 2) {
            // ls
            while ((file = readdir(folder)) != NULL) {
                if (file->d_name[0] == '.') {
                    continue;
                }
                printf("%s ", file->d_name);
            }
            printf("\n");

        } else if (argc == 3) {
            
            if (strcmp(argv[1], "-a") == 0) {
                // ls -a
                while ((file = readdir(folder)) != NULL) {
                    printf("%s ", file->d_name);
                }
                printf("\n");

            } else if (strcmp(argv[1], "-l") == 0) {
                // ls -l
                struct stat fileInfo;
                while ((file = readdir(folder)) != NULL) {
                    if (file->d_name[0] == '.') {
                        continue;
                    }
                    if (stat(file->d_name, &fileInfo) != -1) {

                        if (file->d_type == DT_DIR) {
                            printf("d");
                        } else if (file->d_type == DT_REG) {
                            printf("-");
                        } else if (file->d_type == DT_LNK) {
                            printf("l");
                        } else if (file->d_type == DT_SOCK) {
                            printf("s");
                        }

                        if (fileInfo.st_mode & S_IRUSR) {
                            printf("r");
                        } else {
                            printf("-");
                        }
                        if (fileInfo.st_mode & S_IWUSR) {
                            printf("w");
                        } else {
                            printf("-");
                        }
                        if (fileInfo.st_mode & S_IXUSR) {
                            printf("x");
                        } else {
                            printf("-");
                        }

                        if (fileInfo.st_mode & S_IRGRP) {
                            printf("r");
                        } else {
                            printf("-");
                        }
                        if (fileInfo.st_mode & S_IWGRP) {
                            printf("w");
                        } else {
                            printf("-");
                        }
                        if (fileInfo.st_mode & S_IXGRP) {
                            printf("x");
                        } else {
                            printf("-");
                        }

                        if (fileInfo.st_mode & S_IROTH) {
                            printf("r");
                        } else {
                            printf("-");
                        }
                        if (fileInfo.st_mode & S_IWOTH) {
                            printf("w");
                        } else {
                            printf("-");
                        }
                        if (fileInfo.st_mode & S_IXOTH) {
                            printf("x ");
                        } else {
                            printf("- ");
                        }
                            
                        printf("%lu ", fileInfo.st_nlink);

                        struct passwd *pw = getpwuid(fileInfo.st_uid);
                        if (pw != NULL) {
                            printf("%s ", pw->pw_name);
                        }
                        struct group  *gr = getgrgid(fileInfo.st_gid);
                        if (gr != NULL) {
                            printf("%s ", gr->gr_name);
                        }

                        printf("%ld ", fileInfo.st_size);

                        struct tm* time = localtime(&fileInfo.st_ctime);
                        printf("%02d/%02d/%d %02d:%02d ", time->tm_mday, (time->tm_mon +1), (time->tm_year +1900), time->tm_hour, time->tm_min);

                        printf("%s \n", file->d_name);
                    }
                }

            } else {
                printf("ls command failed: invalid argument(s) \n");
            }

        } else {
            printf("ls command failed: too many arguments \n");
        }

        closedir(folder);

    } else {
        printf("ls command failed: couldn't access folder \n");
    }

    return 0;
}
