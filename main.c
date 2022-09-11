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
    char input_buffer[32768];
    while(fgets(input_buffer, 32768, stdin) != NULL) {
        char *pch;
        char *commands[1024];
        int commandsCount = 0;
        for (pch = strtok(input_buffer, ";\n"); pch && commandsCount < 1024; pch = strtok(NULL, ";\n")) {
            commands[commandsCount++] = pch;
        }
        for (int j = 0; j < commandsCount; j++) {
            char *ptr;
            char *oneLineCommand[1024];
            int count = 0;
            for (ptr = strtok(commands[j], " \n"); ptr && count < 1024; ptr = strtok(NULL, " \n")) {
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
    return 0;
}
