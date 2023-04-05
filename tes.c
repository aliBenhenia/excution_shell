#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
typedef struct t_data{
    int var;
    struct t_data *next;
}t_data;
t_data	*addnew(int var, char *value)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->var = var;
	new->next = NULL;
	return (new);
}
void func2(t_data **data)
{
    *data = addnew(55,"ihu");
}
void func1(t_data **data)
{
    func2(data);
}
int main(int argc, char const *argv[])
{
    t_data *data = malloc(sizeof(t_data));
    func1(&data);
    if (data)
        printf("%d\n",data->var);
    return 0;
}
