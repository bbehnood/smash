#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>

#define MAX_TOKENS 64

char** parse_line(char* line)
{
    static char* tokens[MAX_TOKENS];
    int          i = 0;

    char* token = strtok(line, " \t\n");

    while (token && i < MAX_TOKENS)
    {
        tokens[i++] = token;
        token       = strtok(NULL, " \t\n");
    }

    tokens[i] = NULL;

    return tokens;
}

void execute_command(char** argv)
{
    if (!argv || !argv[0])
    {
        return;
    }

    pid_t pid    = fork();
    int   status = 0;

    if (pid == 0)
    {
        execvp(argv[0], argv);

        perror("exec");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}

int main(void)
{
    char*  line = NULL;
    size_t len  = 0;

    while (true)
    {
        printf("smash> ");
        fflush(stdout);

        if (getline(&line, &len, stdin) == -1)
        {
            printf("\n");
            break;
        }

        char** argv = parse_line(line);
        execute_command(argv);
    }

    free(line);

    return EXIT_SUCCESS;
}
