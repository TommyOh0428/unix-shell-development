#include <stdlib.h>
#include <string.h>

char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;

    // using the library function strtok, can split the string by the character
    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }

    // if the input is like "ls -l -h -a", the function will create the array with
    // ["ls", "-l", "-h", "-a", NULL]
    // and return the pointer to this array
    command[index] = NULL;
    return command;
}