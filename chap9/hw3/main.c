#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
#define SHELL_PROMPT "[shell] "

int parse_command(char *input, char **args) {
    int count = 0;
    char *token;

    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

    token = strtok(input, " ");
    while (token != NULL && count < MAX_ARGUMENTS - 1) {
        args[count++] = token;
        token = strtok(NULL, " ");
    }
    args[count] = NULL;
    
    return count;
}

void execute_command(char **args) {
    pid_t pid;
    int status;

    if (args[0] == NULL) {
        return;
    }

    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else {
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid failed");
        }
    }
}


int main() {
    char input_line[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGUMENTS];

    while (1) {
        printf("%s", SHELL_PROMPT); 
        
        if (fgets(input_line, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\nExiting shell...\n");
            break;
        }

        int num_args = parse_command(input_line, args);

        if (num_args > 0) {
            execute_command(args);
        }
    }

    return 0;
}
