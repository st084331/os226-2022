#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int retcodeInt = 0;

int echo(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        printf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');
    }
    return argc - 1;
}

int retcode(int argc, char *argv[]) {
    printf("%d\n", retcodeInt);
    return 0;
}

int main(int argc, char *argv[]) {
    char retcodeCommand[8] = "retcode";
    char echoCommand[5] = "echo";
    for (int i = 1; i < argc; ++i) {
        FILE *fp;
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            retcodeInt = -1;
        } else {
            char *line = NULL;
            size_t len = 0;
            while (getline(&line, &len, fp) != -1) {
                char *pch;
                char *commands[1024];
                int commandsCount = 0;
                for (pch = strtok(line, ";\n"); pch && commandsCount < 1024; pch = strtok(NULL, ";\n")) {
                    commands[commandsCount++] = pch;
                }
                for (int i = 0; i < commandsCount; i++) {
                    char *ptr;
                    char *oneLineCommand[1024];
                    int count = 0;
                    for (ptr = strtok(commands[i], " \n"); ptr && count < 1024; ptr = strtok(NULL, " \n")) {
                        oneLineCommand[count++] = ptr;
                    }
                    if (count > 0) {
                        if (strcmp(echoCommand, oneLineCommand[0]) == 0) {
                            retcodeInt = echo(count, oneLineCommand);
                        }
                        if (strcmp(retcodeCommand, oneLineCommand[0]) == 0) {
                            retcodeInt = retcode(count, oneLineCommand);
                        }
                    } else {
                        retcodeInt = 0;
                    }
                }
            }
            fclose(fp);
            if (line)
                free(line);
        }
    }
    return 0;
}
