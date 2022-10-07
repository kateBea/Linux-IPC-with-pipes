#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

void usage(void)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "Usage: ipc folder_dir\n");
    write(STDOUT_FILENO, buffer, strlen(buffer));
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        usage();
        return 0;
    }

    int pipe_[2];
    char buffer[BUFFER_SIZE];
    pid_t children[2];

    pipe(pipe_);

    children[0] = fork();

    if (!children[0])
    {
        dup2(pipe_[1], STDOUT_FILENO);
        close(pipe_[1]);
        close(pipe_[0]);

        char* const arguments[] =
        {
            "ls",
            argv[1],    // folder directory
            "-l",       // use a long listing format
            "-a",       // do not ignore entries starting with .
            (char*)NULL,
        };

        execvp("ls", arguments);
        perror("Error execvp syscall ls child...");
        exit(1);
    }

    children[1] = fork();

    if (!children[1])
    {
        dup2(pipe_[0], STDIN_FILENO);
        close(pipe_[1]);
        close(pipe_[0]);

        char* const arguments[] =
        {
            "less",
            (char*)NULL,
        };

        execvp("less", arguments);
        perror("Error execvp syscall less child...");
        exit(1);
    }

    close(pipe_[1]);
    close(pipe_[0]);

    int status;
    pid_t child;

    while ((child = waitpid(-1, &status , 0)) > 0)
    {
        if (WIFEXITED(status))
            sprintf(buffer, "Child %i terminated normally with exit code %i\n",
                child, WEXITSTATUS(status));
        else
            sprintf(buffer, "Child %i terminated abnormally\n", child);

        write(STDOUT_FILENO, buffer, strlen(buffer));
    }

    return 0;
}
