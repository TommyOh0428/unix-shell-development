#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../../include/function.h"

int pwd_function(char** command) {
    if (strcmp(command[0], "pwd") == 0) {
        // check if there are more than one paramter
        if (command[1] != NULL) {
            const char* msg = FORMAT_MSG("pwd", TMA_MSG);
            write(STDERR_FILENO, msg, strlen(msg));
            return -1;
        } else {
            char* pwd_path = getcwd(NULL, 0);
            write(STDOUT_FILENO, pwd_path, strlen(pwd_path));
            free(pwd_path);
        }
    } else {
        // error case
        const char* msg = FORMAT_MSG("pwd", GETCWD_ERROR_MSG);
        write(STDERR_FILENO, msg, strlen(msg));
        return -1;
    }
    return 0;
}