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
    if((*a) == NULL)
    {
        (*a) = new;
    }
    else
    {
        head = (*a);
        new->next = NULL;
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
int check_if_in_env(char *s,char *value, t_export *env)
{
    t_export *head;

    head = env;
    while (head)
    {
        if (head->var == s)
        {
            head->value = value;
            return (1);
        }
        head= head->next;
    }
    return (0);
}

void    add_var_in_list(t_export **data,t_env_list **env_list, char *str)
{
    char    **var;
    t_env_list *variable;
    t_export *variable1;

    if (check_if_equal_is(str))
    {
        var = ft_split(str,'=');
        if(check_if_in_env(var[0],var[1],*data))
        {
                // stop here.. for modifying
        }
        variable1 = addnew(var[0],var[1]);
        addback_export(data,variable1);
        variable = addnew2(var[0],var[1]);
        addback_env(env_list,variable);
    }
    else
    {
        var = ft_split(str,'=');
        variable1 = addnew(var[0],"empty");
        addback_export(data,variable1);
    }
}

void    do_export(char *str[], char *env[],t_export **data, t_env_list **env_list)
{
    int i;
    int j;

    i = 1;
    j = 0;
    f = 0;
    if (str[1] == NULL)
    {
		t_export *head = (*data);
        while (head)
        {
            if(head->value == "empty")
                printf("%s \n",head->var);
            else
                 printf("%s = %s\n",head->var,head->value);
            head = head->next;
        }
    }
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (ft_isalnum(str[i][j]) == 0)
            {
                printf("error in : %s\n",str[i]);
                break;
            }
            else if (str[i][j + 1] == '\0')
                add_var_in_list(data,env_list, str[i]);
            j++;
        }
        i++;
    }
}

void    excution(t_cmd_line *cmd_line, char *env[],t_env_list **env_list , t_export **data)
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
		t_env_list *head = (*env_list);
        while (head)
        {
            printf("%s = %s\n",head->name,head->value);
            head = head->next;
        }
	}
	else if (ft_strcmp(cmd_line->str[0],"pwd") == 0)
	{
		do_pwd();
	}
	else if (ft_strcmp(cmd_line->str[0],"export") == 0)
	{
		do_export(cmd_line->str,env,data,env_list);
	}
	else
	{
		if (size_of_list(cmd_line) == 1)
			excute_one_cmd(cmd_line,env);
		else if(size_of_list(cmd_line) > 1)
			do_pipes(cmd_line, size_of_list(cmd_line),env);
	}
}