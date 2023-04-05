#include "minishell.h"

void    do_pipes(t_cmd_line *data, int len,char *env[])
{
    int i;
    int pid;
    int fd[len][2];

    i = 0;
    while (i < len)
        pipe(fd[i++]);
    while (i < len)
    {
        pid = fork();
        if (pid == 0)
        {
            dup2(fd[1],1);
            dup2(fd[0],0);
        }
    }
}