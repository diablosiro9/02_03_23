/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:03:59 by dojannin          #+#    #+#             */
/*   Updated: 2023/02/18 17:10:14 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

t_list *lexer(t_list *str)
{
    t_list *list;
    int i;
    char **tab = NULL;

    i = 0;
    list = NULL;
    tab = ft_split((char *)str->content);
    while (tab[i])
    {
        ft_lstadd(&list, ft_lstnew(tab[i]));
        i++;
    }
    afflist(list, "Lexer");
    tokenizateur(list);
    return (list);
}

void afftoken(t_token *list, char *name)
{
    (void)name;
    while (list)
    {
        printf("\e[0;31mToken : [%s]\e[0m", list->value);
        printf("\e[0;31mToken : [%d]\n\e[0m", list->t_type);
        list = list->next;
    }
}

int	token_size()
{
	int	i = 0;
	t_data	ptr = g_data;

	if (g_data.token)
	{
		while (g_data.token)
		{
			i++;
			g_data.token = g_data.token->next;
		}
	}
	g_data = ptr;
	return (i);
}

void	delete_token(t_token **l)
{
	t_token	*tmp;

	tmp = (*l);
	while ((*l) != NULL)
	{
		tmp = (*l);
		(*l) = (*l)->next;
		free(tmp);
	}
	free(*l);
}
