#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
#define SHELL_PROMPT "Pls input cmd : "

bool parse_command(char *input, char **args) {
    char *saveptr;
    char *token;
    int count = 0;
    bool background = false;

    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

    token = strtok_r(input, " ", &saveptr);
    while (token != NULL && count < MAX_ARGUMENTS - 1) {
        args[count++] = token;
        token = strtok_r(NULL, " ", &saveptr);
    }
    
    if (count > 0 && strcmp(args[count - 1], "&") == 0) {
        background = true;
        args[count - 1] = NULL;
    } else {
        args[count] = NULL;
    }

    return background;
}

void execute_command(char **args, bool background) {
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
        if (background) {
            printf("[Process %d] running in background\n", pid);
        } else {
            if (waitpid(pid, &status, 0) < 0) {
                perror("waitpid failed");
            }
        }
    }
}


int main() {
    char input_line[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGUMENTS];
    bool background_flag;

    while (1) {
        while (waitpid(-1, NULL, WNOHANG) > 0); 
        
        printf("%s", SHELL_PROMPT); 
        
        if (fgets(input_line, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\nExiting shell...\n");
            break;
        }

        background_flag = parse_command(input_line, args);

        if (args[0] != NULL) {
            execute_command(args, background_flag);
        }
    }

    return 0;
}
