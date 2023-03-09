#include "../../include/include.h"


//write a function that takes a string and returns a list of tokens (t_type)

//t_token is an enum with the following values: PIPE, REDIR, WORD, SPACE, END

//the list should be a list of t_list, where each t_list contains a t_token and a char*

//the list should be terminated by a t_list with type END

//the list should be freed by the caller


t_token	*ft_token_new(int type, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->t_type = type;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_token *ft_token_add(t_token **alst, t_token *new)
{
    t_token *tmp;

    tmp = *alst;
    if (tmp)
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    else
        *alst = new;
    return (new);
}

void	init_type(int type, char *value)
{
    // if (!token)
    // {
	// 	printf("malloc error\n");
	// 	exit(-127);
	// }
	if (ft_token_new(type, value) != NULL)
		ft_token_add(&g_data.token, ft_token_new(type, value));
	// return (token);
}

t_token *tokenizateur(t_list *list)
{
	// t_token	*token = NULL;
	while (list != NULL && list->content != (void *)0)
	{
		if (ft_strchr(list->content, '|'))
		{
			printf("PIPE\n");
			init_type(PIPE, list->content);
		}
		else if (ft_strchr(list->content, '$'))
		{
			printf("DOLLAR\n");
			init_type(DOLLAR, list->content);
		}
        else if (ft_strchr(list->content, '>'))
        {
            printf("REDIR\n");
           	init_type(REDIR, list->content);
        }
        else if (ft_strchr(list->content, '<'))
        {
            printf("RREDIR\n");
            init_type(REDIR, list->content);
            if (!list->next || access())
        }
        else if (ft_strchr(list->content, '"'))
        {
            printf("QUOTE\n");
            init_type(QUOTE, list->content);
        }
        else if (ft_strchr(list->content, '\''))
        {
            printf("SQUOTE\n");
            init_type(SQUOTE, list->content);
        }
        else if (ft_strchr(list->content, '-'))
        {
            printf("OPTION\n");
            init_type(OPTION, list->content);
        }
        else
        {
            printf("WORD\n");
			printf("CONTENT == %s\n", (char *)list->content);
			// if (ft_strncmp(list->content, "(null)", ft_strlen(list->content)) != 0)
        	init_type(WORD, list->content);
        }
        list = list->next;
    }
    return (NULL);
}
