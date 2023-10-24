#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
// A data structure to store environment variables
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "Libft/src/libft.h"
// A simplified function to set or update environment variables
// void setEnvVariable(char* name, char* value) {
//     for (int i = 0; i < envCount; i++) {
//         if (strcmp(env[i].name, name) == 0) {
//             free(env[i].value); // Free old value
//             env[i].value = strdup(value);
//             return;
//         }
//     }
    
//     env[envCount].name = strdup(name);
//     env[envCount].value = strdup(value);
//     envCount++;
// }
// void ft_export()
// {
//     extern char **environ;
//     for(char **env = environ; *env != NULL; env++)
//         printf("declare -x %s\n", *env);
// }
void ft_cd()
{
    char *home;
    // char cwd[PATH_MAX];
    home = getenv("HOME");
    printf("\tHome:\t%s\n", home);
    chdir(home);
    // getcwd(cwd, sizeof(cwd));
    // printf("%s\n", cwd);
}
void ft_pwd(void)
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
}
// int ft_strlen(char *str)
// {
//     int i =0;
//     while(str[i])
//         i++;
//     return i;
// }
typedef struct s_env
{
    const char *name;
    char *value;
} t_env;
void print_var(char **envp)
{
    int i = 0;
    while(envp[i] != NULL)
    {
        printf("%d\t%s\n",i, envp[i]);
        i++;
    }
}
int main(int argc, char **argv, char **envp)
{
    int i  =0;
    while(envp[i] != NULL)
        i++;
    t_env *env;
    env = (t_env *)malloc(sizeof(t_env) * i);
    i = 0;
    int j = 0;
    while(envp[i] != NULL)
    {
        char **tmp = ft_split(envp[i], '=');
        env[i].name = (const char *)malloc(sizeof(char) * ft_strlen(tmp[0]) + 1); 
        env[i].value = (char *)malloc(sizeof(char) * ft_strlen(tmp[1]) + 1);
        env[i].name = tmp[0];
        env[i].value = tmp[1];
        i++;
        free(tmp[0]);
        free(tmp[1]);
        free(tmp);
    }
    env[i].name = NULL;
    env[i].value = NULL;
    // env[i] = NULL;
    // print_var(envp);
    while(j < i)
    {
        printf("%s=%s\n", env[j].name, env[j].value);
        j++;
    }
    // while(j > 0)
    // {
    //     free((void *)env[j].name);
    //     free(env[j].value);
    //     j--;
    // }
    // free(env);
}