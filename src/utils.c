#include "../includes/pipex.h"

char    *get_cmd_path(char *cmd, char **envp)
{
    char    *path;
    char    **paths;
    int     i;

    i = 0;
    while (envp[i] && strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (!envp[i])
        return (NULL);
    paths = ft_split(envp[i] + 5, ':');
    i = 0;
    while (paths[i])
    {
        path = malloc(strlen(paths[i]) + strlen(cmd) + 2);
        if (!path)
            return (NULL);
        sprintf(path, "%s/%s", paths[i], cmd);
        if (access(path, X_OK) == 0)
            return (path);
        free(path);
        i++;
    }
    return (NULL);
}

void    execute_command(char *cmd, char **envp)
{
    char    **args;
    char    *cmd_path;

    args = ft_split(cmd, ' ');
    if (!args)
    {
        perror("ft_split");
        exit(EXIT_FAILURE);
    }
    cmd_path = get_cmd_path(args[0], envp);
    if (!cmd_path)
    {
        ft_printf("Command not found: ");
        ft_printf(args[0]);
        ft_printf("\n");
        exit(EXIT_FAILURE);
    }
    execve(cmd_path, args, envp);
    perror("execve");
    exit(EXIT_FAILURE);
}

void    here_doc_mode(char *limiter)
{
    int     fd;
    char    *line;

    fd = open(".here_doc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        ft_printf("heredoc> ");
        line = get_next_line(0);
        if (!line || strcmp(line, limiter) == 0)
            break;
        write(fd, line, strlen(line));
        free(line);
    }
    free(line);
    close(fd);
}
