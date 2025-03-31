#include "../includes/pipex.h"

void    child_process(char *cmd, char **envp)
{
    execute_command(cmd, envp);
}

void    multiple_pipes(int argc, char **argv, char **envp)
{
    int i;
    int fd[2];
    pid_t pid;
    int infile;
    int outfile;
    int doc_tmp;

    infile = open(argv[1], O_RDONLY);
    outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (infile == -1 || outfile == -1)
    {
        perror("File error");
        exit(EXIT_FAILURE);
    }
    dup2(infile, 0);
    i = 2;
    while (i < argc - 2)
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            dup2(fd[1], 1);
            close(fd[0]);
            child_process(argv[i], envp);
        }
        close(fd[1]);
        dup2(fd[0], 0);
        i++;
    }
    dup2(outfile, 1);
    child_process(argv[argc - 2], envp);
}


int main(int argc, char **argv, char **envp)
{
    if (argc < 5)
    {
        ft_printf("Usage: ./pipex infile cmd1 cmd2 ... outfile\n");
        return (EXIT_FAILURE);
    }
    if (ft_strcmp(argv[1], "here_doc") == 0)
    {
        if (argc < 6)
        {
            ft_printf("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... outfile\n");
            return (EXIT_FAILURE);
        }
        here_doc_mode(argv[2]);
        argv[1] = ".here_doc_tmp";
    }
    multiple_pipes(argc, argv, envp);
    return (EXIT_SUCCESS);
}