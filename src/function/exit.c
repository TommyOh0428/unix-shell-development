#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../../include/function.h"

int exit_function(char** command) {
    if (strcmp(command[0], "exit") == 0) {
        // check if there are more than one parameter
        if (command[1] != NULL) {
            const char* msg = FORMAT_MSG("exit", TMA_MSG);
            write(STDERR_FILENO, msg, strlen(msg));
            return -1;
        }
        free(command);
        return 1;
    }
    return 0;
}