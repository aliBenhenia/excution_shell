#include "minishell.h"
void	print_env(t_env_list **env)
{
	t_env_list *head = (*env);
	while (head)
	{
		printf("%s=\"%s\"\n",head->name,head->value);
		head = head->next;
	}
}