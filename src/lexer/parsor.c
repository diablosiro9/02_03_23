/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:57:41 by dojannin          #+#    #+#             */
/*   Updated: 2023/02/28 02:07:02 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"


int check_name(char *str, t_list *name)
{
    while (name)
    {
        if (ft_strcmp(str, (char *)name->content) == 0)
            return (1);
        name = name->content;
    }
    return (0);
}

int closed_elem(char *str, char c)
{
	int i = 0;
	int flag = 0;
	int counter = 0;
	char *start = ft_strchr(str, c);
	
	if (start == NULL)
		return (1);
	while (start[i])
	{
		if (counter == 1 && start[i] == c)
		{
			counter = 0;
			flag = 0;
		}
		if (flag == 1 && start[i] == c)
		{
			counter = 1;
			flag = 0;
		}
		if (start[i] == c && counter != 1)
			flag = 1;
		i++;
	}
	return (counter);
}

int checking_closed(char *tp)
{
	if (!tp)
		return (-2);
	int val_test = closed_elem(tp, '"');
	if (val_test == 0)
		return (0);
	val_test = closed_elem(tp, '\'');
	if (val_test == 0)
		return (-1);
	return (val_test);
}

void	*split_cmd_file()
{
	t_token	*tmp = g_data.token;
	char	*path;
	char	**tab_path;
	char	*tmp1;
	char	*tmp2;
	int		i = 0;

	if (tmp)
	{
		while (tmp)
		{
			if (tmp->t_type == 3)
			{
				if (ft_strlen(tmp->value) > 1)
				{
					//printf("tmp->value == %s\n", tmp->value);
					path = search_env_content(g_data.env, "$PATH");
					if (path == NULL)
						return (NULL);
					printf("sorti\n");
					tab_path = ft_oldsplit(path, ':');
					path = tmp->value;
					//printf("path == %s\n", path);
					i = 0;
					while (tab_path[i])
					{
						tmp1 = ft_strjoin_bis(tab_path[i], "/");
						tmp2 = ft_strjoin_bis(tmp1, path);
						free(tmp1);
						if (access(tmp2, X_OK) == 0)
						{
							//printf("ACCESS RETURN 0\n");
							free_tab(tab_path);
							tmp->t_type = COMMAND;
							tmp->value = tmp2;
							//printf("AVANT LENVOIE == %s\n", tmp2);
							//ft_exec(tmp2);// je la recup ici pour le moment car tu me fais deja le acces
							//et y a donc le path complet vers la commande a executer
							return (tmp2);
						}
						free(tmp2);
						i++;
					}
					free_tab(tab_path);
					// if (tmp->value == NULL && tmp->next == NULL) //si return null et que dautres '$' apparaissent apres, tu fais quoi ? 
					// 	return (NULL);
				}
			}
			tmp = tmp->next;
		}
	}
	printf("fin split cmd file\n");
	return ((void *)g_data.token->value);
}

void	*parsor(t_list *str)
{
	// t_list	*list = NULL;
	// int		i = 0;
	afflist(str, "PARSOR");
	if (find_all_dollars() == NULL)
		return (NULL);
	if (solo_command() == NULL)
		return (NULL);
	else if (manage_double() == NULL)
		return (NULL);
	afftoken(g_data.token, "G_DATA_TOKEN");
	//printf("fin parsor\n");
	// split_cmd_file();
	afftoken(g_data.token, "G_DATA_TOKEN");
	return (NULL);
}