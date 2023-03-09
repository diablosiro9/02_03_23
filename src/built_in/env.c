/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:00:53 by imac21            #+#    #+#             */
/*   Updated: 2023/03/02 10:37:38 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

char    *ft_sub(char const *s, unsigned int start, size_t len)
{
    char *str = NULL;
    size_t i;

    i = 0;
    // if (!s)
    //     return (NULL);
    if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    while (i < len)
    {
        str[i] = s[start + i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

t_env	*ft_envnew(char *name, char *content, int i)
{
	(void)i;
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->content = content;
	new->next = NULL;
	return (new);
	
}

void	ft_envadd(t_env **lst, t_env *new)
{
	t_env	*tmp = NULL;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (*lst)
		tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}


t_env *get_env(char **env)
{
    int i = 0;
    t_env *list = NULL;
    
    // list = malloc(sizeof(t_env *) * 1000);
    // if (!list)
    // {
    //     printf("malloc error\n");
    //     exit(-127);
    // }
    while (env[i])
    {
		// list = ft_envnew(ft_sub(env[i], 0, ft_strchr(env[i], '=') - env[i]), \
		// ft_sub(env[i], starter_env(env[i]), ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i])), i);
        ft_envadd(&list, ft_envnew(ft_sub(env[i], 0, ft_strchr(env[i], '=') - env[i]), \
		ft_sub(env[i], starter_env(env[i]), ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i])), i));
		// list[i].content =  ft_sub(env[i], starter_env(env[i]), ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i]));
		// list[i].next = NULL;
		i++;
    }
	list->num_vars = i;
    return (list);
}

// trouver le moyen de passer plusieurs para, tant quon trouve pas pipe
void	ft_env(char	*s)
{
	t_env	*tmp = NULL;
	char	*copy = s;
	// int		i = 0;
	int		flag = -1;
	t_token	*tmp_token = g_data.token;

	tmp = g_data.env;
	if (tmp != NULL)
	{
		if (s == NULL)
		{
			while (tmp != NULL)
			{
				printf("%s%s\n", tmp->name, tmp->content);
				tmp = tmp->next;
			}
		}
		else
		{
			tmp_token = tmp_token->next;
			while (tmp_token != NULL)
			{
				copy = tmp_token->value;
				if (ft_strchr(copy, '=') == NULL)
					flag = 0;
				tmp_token = tmp_token->next;
			}
			if (flag == -1)
			{
				while (tmp != NULL)
				{
					printf("%s%s\n", tmp->name, tmp->content);
					tmp = tmp->next;
				}
				tmp_token = g_data.token;
				tmp_token = tmp_token->next;
				while (tmp_token != NULL)
				{
					printf("%s\n", tmp_token->value);
					tmp_token = tmp_token->next;
				}
			}
			else
				printf("env: %s: No such file or directory\n", s);
		}
	}
}
/*
void	init_data_env(char **env)
{
	int		i;
	char	**tableau;

	i = 0;
	tableau = ft_split(env[i++], '=');
	g_data.env = ft_lstnew_env(ft_strdup(tableau[0]), ft_strdup(tableau[1]));
	free_tab(tableau);
	while (env[i])
	{
		tableau = ft_split(env[i], '=');
		ft_lstadd_back_env(&g_data.env, ft_lstnew_env(ft_strdup(tableau[0]),
				ft_strdup(tableau[1])));
		free_tab(tableau);
		i++;
	}
}*/