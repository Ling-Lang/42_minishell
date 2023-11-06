#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "Libft/src/libft.h"
extern char **__environ;
int main(int argc, char **argv, char *envp[])
{
    int ret;
    pid_t child_pid = fork();
    // int i = 0;
    char *args[2];
    args[0] = "ls";
    args[1] = "-l";
    if (child_pid == 0) 
    {
        // printf("%s\n", environ[6]);
        ret = execve(args[0], args, __environ);
        if(ret == -1)
            perror("WHY");
            exit(0);

    } else if (child_pid < 0) {
        perror("fork");
    } else {
        // Parent process
        waitpid(child_pid, NULL, 0);
    }
    return 0;
}