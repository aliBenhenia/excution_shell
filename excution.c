#include "minishell.h"
t_export	*addnew(char *var, char *value)
{
	t_export	*new;

	new = malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	new->var = var;
	new->value = value;
	new->next = NULL;
	return (new);
}
void	addback_export(t_export **a, t_export *new)
{
  t_export  *head;

    head = (*a);
    new->next = NULL;
    if((*a) == NULL)
        (*a) = new;
    else
    {
        head = (*a);
        while (head->next)
        {
            head = head->next;
        }
        head->next = new;
    }
}

t_env_list	*addnew2(char *var, char *value)
{
	t_env_list	*new;

	new = malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->name = var;
	new->value = value;
	new->next = NULL;
	return (new);
}
void	addback_env(t_env_list **a, t_env_list *new)
{
  t_env_list  *head;

    new->next = NULL;
    head = (*a);
    if(head == NULL)
    {
         (*a) = new;
    }
    else
    { 
        head = (*a);
        while (head->next)
            head = head->next;
        head->next = new;
    }
}
void    do_env(char *env[])
{
    int i;

    i = 0;
    while (env[i])
    {
        ft_putstr(env[i]);
        ft_putstr("\n");
        i++;
    }
}

void    do_pwd(void)
{
   char cwd[2000];

   if (getcwd(cwd, sizeof(cwd)) != NULL)
       ft_putstr(cwd);
   else
       perror("getcwd() error");
    ft_putstr("\n");
}

int check_if_equal_is(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=' && str[i + 1])
        {
            return (1);
        }
        i++;
    }
    return (0);
}

void    add_var_in_list(t_export **data, char *str)
{
    char    **var;
    t_export *variable;

    if (check_if_equal_is(str))
    {
        var = ft_split(str,'=');
        variable = addnew(var[0],var[1]);
        addback_export(data,variable);
    }
}

void  fill_env(char *env[] ,t_env_list **data)
{
    int i;
    char    **name;
    t_env_list *n;

    i = 0;
    while (env[i])
    {
        name = ft_split(env[i], '=');
        n = addnew2(name[0], name[1]);
        addback_env(data,n);
        i++;
    }
}

void    do_export(char *str[], char *env[])
{
    int i;
    int j;
    int f;
    t_export    *data;
    t_env_list  *env_list;

    i = 1;
    j = 0;
    f = 0;
    data = malloc(sizeof(t_export));
    data = NULL;
    env_list = malloc(sizeof(t_env_list));
    env_list = NULL;
    fill_env(env,&env_list);
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (ft_isalnum(str[i][j]) == 0)
            {
                i++;
                f = 1;
                printf("error\n");
                break;
            }
            else if (str[i][j + 1] == '\0')
            {
                add_var_in_list(&data, str[i]);
            }
            j++;
        }
        i++;
    }
  t_env_list *new;
   if (data)
   {
      new = addnew(data->var, data->value);
      addback_env(&env_list,new);
      data = data->next;
   }
        // t_env_list *head = env_list;
        // while (head)
        // {
        //     printf("--> %s = %s \n",head->name , head->value);
        //     head = head->next;
        // }

    if(i == 1)
    {
       do_env(env);
    }
    // if (f == 1)
    //    perror("export");
}

void    excution(t_cmd_line *cmd_line, char *env[])
{
    if (cmd_line->str[0] == NULL)
		return ;
    else if (ft_strcmp(cmd_line->str[0],"echo") == 0)
	{
		handle_echo(cmd_line);
	}
	else if (ft_strcmp(cmd_line->str[0],"cd") == 0)
	{
		do_cd(cmd_line->str[1]);
	}
	else if (ft_strcmp(cmd_line->str[0],"env") == 0)
	{
		do_env(env);
	}
	else if (ft_strcmp(cmd_line->str[0],"pwd") == 0)
	{
		do_pwd();
	}
	else if (ft_strcmp(cmd_line->str[0],"export") == 0)
	{
		do_export(cmd_line->str,env);
	}
	else
	{
		if (size_of_list(cmd_line) == 1)
			excute_one_cmd(cmd_line,env);
		else if(size_of_list(cmd_line) > 1)
			do_pipes(cmd_line, size_of_list(cmd_line));
	}
}