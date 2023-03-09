/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_parsor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:00:49 by dojannin          #+#    #+#             */
/*   Updated: 2023/02/18 17:13:56 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"


void	checking_solo_name(t_token *tmp)
{
	if (token_size() == 1)
	{
		if (tmp->t_type == 4 || tmp->t_type == 5 || tmp->t_type == 6 
				|| tmp->t_type == 1 || tmp->t_type == 2 )
		{
			if (ft_strlen(tmp->value) < 2)
			{
				if (tmp->t_type == 6)
					printf("Us_Bash: $: command not found\n");
				else if (tmp->t_type == 1 || tmp->t_type == 2)
				{
					printf("Us_Bash2: syntax error near unexpected token 'newline'\n");
				}
				return ;
			}
		}
	}
}

void	*solo_command()
{
	//CRASH SI LE SEUL TOKEN RECU EST UNE REDIR RREDIR PIPE OU OPTION
	t_token	*tmp;

	tmp = g_data.token;
	if (token_size() == 1 && tmp->t_type != 3)
	{
		checking_solo_name(tmp);
		g_data.token = tmp;
	}
	// else
	// {
	// 	printf("Liste de tokens superieur à 1 ou seul un Token_Word\n");
	// 	if (manage_double() == NULL)
	// 	{
	// 		printf("noooon\n");
	// 		return (NULL);
	// 	}
	// }
	// SI SEUL TOKEN EST UN WORD, PEUT ETRE UN FILE OU UNE COMMANDE (CMD PEUT ETRE EXEC SEULE COMME ECHO)
		// DOLLAR PEUT AUSSI, DQUOTE SQUOTE AUSSI 
	printf("fin\n");
	return ((void *)g_data.token->value);
}

void	*manage_double()
{
	t_token	*tmp;

	tmp = g_data.token;
	if (token_size() > 1)
	{
		while (tmp)
		{
			if (tmp->t_type == 0 && tmp->next->t_type == 0)
			{
				printf("Us_Bash: syntax error near unexpected token '|'\n");
				return (NULL);
			}
			tmp = tmp->next;
		}
	}
	return ((void *)g_data.token->value);
}

void	*find_all_dollars()
{
	t_token	*tmp = g_data.token;

	if (tmp)
	{
		while (tmp)
		{
			if (tmp->t_type == 6)
			{
				if (ft_strlen(tmp->value) > 1)
				{
					tmp->value = search_env_content(g_data.env, tmp->value);
					//printf("tmp->value -- %s\n", tmp->value);
					// if (tmp->value == NULL && tmp->next == NULL) //si return null et que dautres '$' apparaissent apres, tu fais quoi ? 
					// 	return (NULL);
				}
				else
					printf("Us_Bash: $: command not found\n");
			}
			tmp = tmp->next;
		}
	}
	return ((void *)g_data.token->value);
}
