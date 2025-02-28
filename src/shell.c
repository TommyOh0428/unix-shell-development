#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "../include/msg.h"
#include "readline/readline.c"

#define BUFFER_SIZE 1024

int main() {
    char** command;
    char input[BUFFER_SIZE];
    pid_t child_pid;
    int status;
    char* cwd;
    ssize_t bytes_read;

    while (1) {
        cwd = getcwd(NULL, 0);

        if (cwd == NULL) {
            const char* msg = FORMAT_MSG("getcwd", GETCWD_ERROR_MSG);
            write(STDERR_FILENO, msg, strlen(msg));
            exit(EXIT_FAILURE);
        }
        write(STDOUT_FILENO, cwd, strlen(cwd));
        write(STDOUT_FILENO, "$ ", 2);
        free(cwd);

        bytes_read = read(STDIN_FILENO, input, BUFFER_SIZE - 1);
        if (bytes_read < 0) {
            const char* msg = FORMAT_MSG("read", READ_ERROR_MSG);
            write(STDERR_FILENO, msg, strlen(msg));
            continue;
        }

        input[bytes_read - 1] = '\0';

        if (bytes_read == 0) {
            break;
        }

        command = get_input(input);
        if (command == NULL) {
            continue;
        }
        child_pid = fork();
        if (child_pid == 0) {
            // child process
            // if the command not working after creating child
            if (execvp(command[0], command) == -1) {
                const char* msg = FORMAT_MSG("shell", EXEC_ERROR_MSG);
                perror(msg);
                exit(EXIT_FAILURE);
            } else {
                execvp(command[0], command);
            }
        } else if (child_pid < 0) {
            // fork failed
            const char* msg = FORMAT_MSG("shell", FORK_ERROR_MSG);
            perror(msg);
            exit(1);
        } else {
            // parent process
            if (waitpid(child_pid, &status, 0) == -1) {
                const char* msg = FORMAT_MSG("shell", WAIT_ERROR_MSG);
                perror(msg);
            }
        }
        free(command);
    }
    return 0;
}