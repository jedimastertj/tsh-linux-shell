#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>

int freq(char c, char* str, int length) {
    int n = 0;
    for (int i = 0; i < length; i++) {
        if (str[i] == c) {
            n++;
        }
    }
    return n;
}

int main() {
    
    char inp[100];
    char inp2[100];
    char* args[30];
    const char sep[2] = " ";
    const char sep2[2] = "\"";
    char* token;
    int argc;
    char currentDirectory[100];

    while (1) {
        argc = 0;
        getcwd(currentDirectory, sizeof(currentDirectory));
        printf("tsh$ ");
        fgets(inp, 100, stdin);
        inp[strlen(inp)-1] = '\0';
        strcpy(inp2, inp);

        token = strtok(inp, sep);
        while (token != NULL) {
            if (argc < 30) {
                args[argc++] = token; 
            }
            token = strtok(NULL, sep);
        }
        args[argc] = NULL;

        int mthcheck = 0;
        if (strcmp(args[argc-1], "&t") == 0) {
            mthcheck = 1;
        }

        if (strcmp(args[0], "cd") == 0) {

            if (argc > 2) {
                printf("cd command failed: too many arguments \n");

            // cd and cd ~
            } else if (argc == 1 || args[1][0] == '~') {
                char home[30];
                strcpy(home, getenv("HOME"));
                chdir(home);
            } else if (chdir(args[1]) != 0) {
                perror("cd command failed");
            }

        } else if (strcmp(args[0], "echo") == 0) {

            if (freq('"', inp2, strlen(inp2)) != 2) {
                printf("echo command failed: need to enclose string within \"\" \n");

            } else {
                int argc2 = 0;
                const char* args2[30];
                token = strtok(inp2, sep2);
                while (token != NULL) {
                    if (argc2 < 30) {
                        args2[argc2++] = token; 
                    }
                    token = strtok(NULL, sep2);
                }
                args2[argc2] = NULL;

                // echo -e
                if (strcmp(args[1], "-e") == 0) {
                    
                    if (args[2][0] == '"' && argc2 == 2) {
                        char sep3[5];
                        sep3[0] = '\0';
                        if (strstr(args2[1], " \\b") != NULL) {
                            strcpy(sep3, " \\b");   
                        } else if (strstr(args2[1], " \\n") != NULL) {
                            strcpy(sep3, " \\n");
                        } else if (strstr(args2[1], " \\t") != NULL) {
                            strcpy(sep3, " \\t");
                        } 

                        if (sep3[0] != '\0') {
                            int argc3 = 0;
                            const char* args3[30];
                            char inp3[100];
                            strcpy(inp3, args2[1]);
                            token = strtok(inp3, sep3);
                            while (token != NULL) {
                                if (argc3 < 30) {
                                    args3[argc3++] = token; 
                                }
                                token = strtok(NULL, sep3);
                            }
                            args3[argc3] = NULL;
                            for (int i = 0; i < argc3; i++) {
                                if (strcmp(sep3, " \\b") == 0) {
                                    printf("%s", args3[i]);
                                } else if (strcmp(sep3, " \\t") == 0) {
                                    printf("%s  ", args3[i]);
                                } else if (strcmp(sep3, " \\n") == 0) {
                                    printf("%s \n", args3[i]);
                                }
                            }
                            if (strcmp(sep3, " \\n") != 0) {
                                printf("\n");
                            }   

                        } else {
                            printf("%s \n", args2[1]);
                        }

                    } else {
                        printf("echo command failed: invalid argument(s) \n");    
                    }
                
                // echo -n
                } else if (strcmp(args[1], "-n") == 0) {
                    if (args[2][0] == '"' && argc2 == 2) {
                        printf("%s", args2[1]);
                    } else {
                        printf("echo command failed: invalid argument(s) \n");    
                    } 

                // echo
                } else if (args[1][0] == '"' && argc2 == 2) {
                    printf("%s \n", args2[1]);

                } else {
                    printf("echo command failed: invalid argument(s) \n");
                }
            }

        } else if (strcmp(args[0], "pwd") == 0) {

            // pwd, pwd -P and pwd -L
            if (argc == 1 || (argc == 2 && (strcmp(args[1], "-P") == 0 || strcmp(args[1], "-L") == 0))) {
                printf("%s \n", currentDirectory);
            } else {
                printf("pwd command failed: invalid argument(s) \n");
            }

        } else if (strcmp(args[0], "ls") == 0) {

            if (mthcheck != 1) {
                int id = fork();
                args[argc++] = currentDirectory;
                args[argc] = NULL;
                if (id == 0) {
                    if (execve("/home/tanishq/Desktop/ls", args, NULL) == -1) {
                        printf("error loading external program \n");
                        return 0;
                    }
                } else if (id > 0) {
                    wait(NULL);
                }

            } else {
                           

            }

        } else if (strcmp(args[0], "cat") == 0) {

            if (mthcheck != 1) {
                int id = fork();
                args[argc++] = currentDirectory;
                args[argc] = NULL;
                if (id == 0) {
                    if (execve("/home/tanishq/Desktop/cat", args, NULL) == -1) {
                        printf("error loading external program \n");
                        return 0;
                    }
                } else if (id > 0) {
                    wait(NULL);
                }

            } else {
                
            }

        } else if (strcmp(args[0], "date") == 0) {

            if (mthcheck != 1) {
                int id = fork();
                if (id == 0) {
                    if (execve("/home/tanishq/Desktop/date", args, NULL) == -1) {
                        printf("error loading external program \n");
                        return 0;
                    }
                } else if (id > 0) {
                    wait(NULL);
                }

            } else {
                
            }

        } else if (strcmp(args[0], "rm") == 0) {

            if (mthcheck != 1) {
                int id = fork();
                args[argc++] = currentDirectory;
                args[argc] = NULL;
                if (id == 0) {
                    if (execve("/home/tanishq/Desktop/rm", args, NULL) == -1) {
                        printf("error loading external program \n");
                        return 0;
                    }
                } else if (id > 0) {
                    wait(NULL);
                }   

            } else {
                
            }

        } else if (strcmp(args[0], "mkdir") == 0) {

            if (mthcheck != 1) {
                int id = fork();
                args[argc++] = currentDirectory;
                args[argc] = NULL;
                if (id == 0) {
                    if (execve("/home/tanishq/Desktop/mkdir", args, NULL) == -1) {
                        printf("error loading external program \n");
                        return 0;
                    }
                } else if (id > 0) {
                    wait(NULL);
                }

            } else {
                
            }

        } else if (strcmp(args[0], "break") == 0 && argc == 1) {
            break;

        } else {
            printf("Invalid command type \n");
        }

    }
     
    return 0;
}
