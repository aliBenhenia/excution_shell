#include "minishell.h"
void    do_pwd(void)
{
   char cwd[2000];

   if (getcwd(cwd, sizeof(cwd)) != NULL)
	   ft_putstr(cwd);
   else
	   perror("getcwd() error");
	ft_putstr("\n");
}

