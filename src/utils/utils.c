/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:09:32 by dojannin          #+#    #+#             */
/*   Updated: 2023/02/18 17:09:57 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

void afflist(t_list *list, char *name)
{
    (void)name;
    while (list)
    {
        // printf("		--------------------\n\
		// | Affichage %s  |\n\
		// ---------------------\n\
		// 	%s\n", name, list->content);
        printf("\e[1;33mToken : [%s]\n\e[0m", (char *)list->content);
        list = list->next;
    }
}

t_list *ft_lstadd(t_list **alst, t_list *new)
{
    t_list *tmp;

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

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

char *ft_strchr(const char *s, int c)
{
    while (*s != (char)c)
    {
        if (!*s++)
            return (NULL);
    }
    return ((char *)s);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void ft_putstr(char *str)
{
    int i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

char *ft_strsub(char const *s, unsigned int start, size_t len)
{
    char *str;
    size_t i;

    i = 0;
    if (!s)
        return (NULL);
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

int	checking_str(char *ref, char *find)
{
	int i = 0;
	int	j = 0;

	if (!ref || !find)
		return (0);
	while (ref[i])
	{
		if (find[j] == '$')
			j++;
		if (ref[i] != find[j])
			return (0);
		i++;
		j++;
	}
	return (1);

}

char	*search_env_content(t_env *env, char *name)
{
	int	i = 0;
	char	*str = name;
	while (i < g_data.env->num_vars && env)
	{
		if (env->name == NULL || !env)
			return (NULL);
		if (checking_str(env->name, str) == 1)
        {
			name = env->content;
			return (&name[1]);
        }
		env = env->next;
		i++;
	}
	return (NULL);
}

char **ft_split (char *str)
{
    int i = 0;
    int j = 0;
    int tmp = 0;
    char **tab = (char **)malloc(sizeof(char *) * 10000); // CHECK TES MALLOCS AMOOUUURRRR -> Il faudrait que tu malloc d'une taille qui représente la réelle taille de ton tableau de char * 
	if (str[i] == '\0')
	{
		tab[0] = (char *)malloc(sizeof(char) * 2);
		tab[0] = " ";
		tab[1] = NULL;
		return (tab);
	}
    while (str[i] != '\0')
    {
        // Splitter par fonction (une fonction pour ce if, les prochain else if et le else)
        if (str[i] == '-')
        {
            tmp = i;
            while (str[i] != ' ' && str[i] != '\0')
                i++;
            tab[j] = ft_strsub(str, tmp, i);
            str = str + i; // Tres stylé
            i = 0;
            j++;
        }
        else if (str[i] == '$')
        {
            tmp = i;
            while (str[i] != ' ' && str[i] != '\0')
                i++;
            tab[j] = ft_strsub(str, tmp, i);
            //is_env(tab[j]);
            str = str + i; 
            i = 0;
            j++;
        }
        else if (str[i] == '"')
        {
            tmp = i;
            i = i + 1;
            while(str[i] != '"')
            {
                i++;
                if (str[i] == '\0')
                    exit(-81);
            }
            i = i + 1;
            tab[j] = ft_strsub(str, tmp, i);
            str = str + i;
            i = 0;
            tmp = 0;
            j++;
        }
        else if (str[i] == '\'')
        {
            tmp = i;
            i = i + 1;
            while(str[i] != '\'')
            {
                if (str[i] == '\0')
				{
					printf("la\n");
					tab[j] = 0;
                    exit(-81);
				}
				i++;
            }
            i = i + 1;
            tab[j] = ft_strsub(str, tmp, i);
            str = str + i;
            i = 0;
            tmp = 0;
            j++;
        }
        else
        {
			while (str[i] == ' ')
				i++;
            if (str[i] != ' ')
            {
                tmp = i;
                while (str[i] != ' ' && str[i] != '\0')
                    i++;
				if (str[i] == ' ')
               		tab[j] = ft_strsub(str, tmp, i - tmp);
				else
               		tab[j] = ft_strsub(str, tmp, i);
				str = str + i;
                i = 0;
                j++;
            }
            else
                i++;
        }
        //printf("tab[%d] = %s et la taille = %d\n", j, tab[j], ft_strlen(tab[j]));
        i++;
    }
    tab[j] = NULL;
    return (tab);
}

void afftab(char **tab)
{
    int i = 0;
    while (tab[i])
    {
        printf("tab[%d] = %s et la taille = %d\n", i, tab[i], ft_strlen(tab[i]));
        i++;
    }
}