#include "minishell.h"

void	handle_red(t_cmd_line *data)
{
	t_cmd_line *head= data;
	int fd;

	
    while (head->redirections)
    {
		
        	if (head->redirections->type == 3)
            {
                head->redirections->fd = open(head->redirections->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
                dup2(head->redirections->fd,STDOUT_FILENO);
				close(head->redirections->fd);
            }
            else if(head->redirections->type == 4)
            {
                    head->redirections->fd = open(head->redirections->file, O_RDONLY , 0777);
                    dup2(head->redirections->fd,STDIN_FILENO);
					close(head->redirections->fd);
            }
            else if(head->redirections->type == 1)
            {
                head->redirections->fd = open(head->redirections->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
                dup2( head->redirections->fd,STDOUT_FILENO);
				close(head->redirections->fd);
            }
        head->redirections = head->redirections->next;
    }
}

void    excution(t_cmd_line *cmd_line, char *env[],t_env_list **env_list , t_export **data)
{
	if(1)
	{
		if (cmd_line == NULL)
			return ;
		// handle_red(cmd_line);
		else if (ft_strcmp(cmd_line->str[0],"echo") == 0)
			handle_echo(cmd_line);
		else if (ft_strcmp(cmd_line->str[0],"cd") == 0)
			do_cd(cmd_line->str[1]);
		else if (ft_strcmp(cmd_line->str[0],"env") == 0)
			print_env(env_list);
		else if (ft_strcmp(cmd_line->str[0],"pwd") == 0)
			do_pwd();
		else if (ft_strcmp(cmd_line->str[0],"export") == 0)
			do_export(cmd_line->str,env,data,env_list);
		else if (ft_strcmp(cmd_line->str[0],"unset") == 0)
			do_unset(cmd_line->str,env,data,env_list);
		else
		{
			if (size_of_list(cmd_line) == 1)
				excute_one_cmd(cmd_line,env);
			else if(size_of_list(cmd_line) > 1)
			{
				do_pipes(cmd_line, size_of_list(cmd_line),env);
				wait(NULL);
			}
		}
	}
}