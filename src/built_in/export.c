/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:15:59 by imac21            #+#    #+#             */
/*   Updated: 2023/03/06 15:12:28 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

t_env	*ft_lstnew_env(char *name, char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->name = name;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*temp;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	else
	{
		temp = *alst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

char	*ft_strjoin_w(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	skip(char **new_env, int *i, t_token **tmp, char *cmd)
{
	while (ft_iswspace(cmd[*i]))
		*i += 1;
	if (*i == ft_strlen(g_data.cmd))
		return (-1);
	if (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		*i += 2;
	*new_env = ft_strdup((*tmp)->value);
	*i += ft_strlen(*new_env);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	printf("=== new_env_Value == %s\n", *new_env);
	return (0);
}

int	check_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s2[i] != '\0')
		return (0);
	return (1);
}

int	ft_same_content(char *name, char *content)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, ft_strlen(tmp->name)))
		{
			printf("crash\n");
			printf("Tmp->content %s\n", tmp->content);
			if (!ft_strncmp(content, tmp->content, ft_strlen(content)))
			{
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	env_exist(char *name)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (check_str(name, tmp->name) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	cmd_unset_assist(char *name, char *content)
{
	t_env	*env;
	t_env	*start;

	start = g_data.env;
	env = g_data.env;
	if (!name)
		return ;
	while (env)
	{
		if (check_str(name, env->name) == 1)
		{
			free(env->content);
			env->content = NULL;
			env->content = ft_strdup(content);
			break ;
		}
		env = env->next;
	}
	g_data.env = start;
}

void	change_env(char *new_env, char *content)
{
	if (env_exist(new_env) == 0)
		ft_lstadd_back_env(&g_data.env,
			ft_lstnew_env(ft_strdup(new_env), ft_strdup(content)));
	else if (ft_same_content(new_env, content) != 1)
		cmd_unset_assist(new_env, content);
	if (new_env)
		free(new_env);
	if (content)
		free(content);
}

void	alpha_export(t_env *env, int fd)
{
	char	*s1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char	*s2 = "abcdefghijklmnopqrstuvwxyz";
	int		i = 0;
	t_env	*tmp = env;
	int flag = 0;

	printf("on est la quand meme\n");
	if (!env)
		return ;
	while (s1[i] && s2[i])
	{
		// printf("on est la quand meme\n");
		tmp = env;
		while (tmp)
		{
			if (ft_isalpha(tmp->name[0]) == 0)
				flag = 1;
			// printf("on est la quand meme\n");
			if (tmp->name[0] == s1[i] || tmp->name[0] == s2[i])
			{
				ft_putstr_fd("declare -x ", fd);
				ft_putstr_fd(tmp->name, fd);
				ft_putstr_fd("=", fd);
				ft_putchar_fd('"', fd);
				ft_putstr_fd(&tmp->content[1], fd);
				ft_putchar_fd('"', fd);
				ft_putchar_fd('\n', fd);
			}
			tmp = tmp->next;
		}
		i++;
	}
	if (flag == 1)
	{
		tmp = env;
		while (tmp)
		{
			if (ft_isalpha(tmp->name[0]) == 0)
			{
				ft_putstr_fd("declare -x ", fd);
				ft_putstr_fd(tmp->name, fd);
				ft_putstr_fd("=", fd);
				ft_putchar_fd('"', fd);
				ft_putstr_fd(&tmp->content[1], fd);
				ft_putchar_fd('"', fd);
				ft_putchar_fd('\n', fd);
			}	
			tmp = tmp->next;
		}
	}
}

void	print_export(t_env *env, int fd)
{
	t_env	*tmp;

	tmp = env;
	alpha_export(tmp, fd);
	// while (tmp)
	// {
	// 	ft_putstr_fd("declare -x ", fd);
	// 	ft_putstr_fd(tmp->name, fd);
	// 	ft_putstr_fd("=", fd);
	// 	ft_putchar_fd('"', fd);
	// 	ft_putstr_fd(&tmp->content[1], fd);
	// 	ft_putchar_fd('"', fd);
	// 	ft_putchar_fd('\n', fd);
	// 	tmp = tmp->next;
	// }
}

char	*reverse_chr(char *s, char c)
{
	int		i = 0;
	char	*res = NULL;

	while (s[i] && s[i] != c)
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return res;
}

int	help_export(t_token **tmp, int *i, int redir)
{
	if (redir == -1)
		redir = 1;
	while (*i < ft_strlen("export"))
		*i += 1;
    if (!(*tmp)->next)
	{
		print_export(g_data.env, 1);
		return (1);
	}
	if (!(*tmp)->next || (*tmp)->next->t_type == 6
		|| (*tmp)->next->t_type == 8)
	{
		print_export(g_data.env, 1);
		return (0);
	}
	(*tmp) = (*tmp)->next;
	return (1);
}

int	main_export(char *content, char *new_env, t_token *tmp, int i)
{
	int z = 0;
	printf("g_data.Cmd[i] == %c\n",g_data.cmd[i]);
	while (tmp)
	{
		printf("entre\n");
		// content = NULL;
		if (z == 1)
			return 1;
		printf("la oue\n");
		// new_env = NULL;
		if (skip(&new_env, &i, &tmp, g_data.cmd) == -1)
			return (1);
		printf("i_Value stp = %d\n", i);
		// if (!g_data.cmd[i]){
		// 	printf("alo\n");

		//     free(new_env);
        //     return 1;
        // }
		i = 0;
		if (g_data.cmd[i] && tmp && ft_iswspace(g_data.cmd[i]) == 1)
		{
			printf("al3\n");

            if (new_env)
		    	free(new_env);
		}
		else if (g_data.cmd[i] && tmp && tmp->t_type == 1)
        {
			printf("al4\n");

			i += 1;
            if (tmp->next)
                tmp = tmp->next;
            while (g_data.cmd[i] && g_data.cmd[i] == '=' && tmp && tmp->t_type == 1)
            {
                if (!*content)
                    content = ft_strdup(tmp->value);
                else
                    content = ft_strjoin_w(content, tmp->value);
                i += 1;
                if (tmp->next)
                    tmp = tmp->next;
            }
        }
    	if (tmp && tmp->value[0] == 0)
        {
			printf("al4\n");
			while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) != 1)
            i += 1;
            if (tmp->next)
            tmp = tmp->next;
        }
		else if (g_data.cmd[i] && ft_isquote(g_data.cmd[i]) == 1)
        {
			printf("al4\n");
            if (!*content)
                content = ft_strdup(tmp->value);
            else
                content = ft_strjoin_w(content, tmp->value);
            if (tmp->next)
                tmp = tmp->next;
            i += 1;
            while (g_data.cmd[i] && ft_isquote(g_data.cmd[i]) != 1)
                i += 1;
            if (g_data.cmd[i] != '\0')
            i += 1;
        }
		else if (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) != 1)
        {	
			printf("al34\n");
			if (content)
				printf("content == %s\n", content);
            if (!content || content == NULL)
                content = ft_strdup(tmp->value);
            else
                content = ft_strjoin_w(content, tmp->value);
			printf("ui\n");
            if (tmp->next)
                tmp = tmp->next;
            i += ft_strlen(content);
        }
		if (env_exist(new_env) == 0)
	        ft_lstadd_back_env(&g_data.env, ft_lstnew_env((reverse_chr(new_env, '=')), ft_strdup(ft_strrchr(new_env, '='))));
        else if (ft_same_content(new_env, content) != 1)
            cmd_unset_assist(new_env, content);
       
	    if (new_env)
            free(new_env);		
        if (content)
            free(content);
		printf("fin \n");
		z++;
	}
	printf("sorti cash\n");
	return (1);
}

int	ft_export(int redir)
{
	t_token	*tmp;
	int			i;
	char		*new_env;
	char		*content;

	content = g_data.cmd;
	new_env = NULL;
	i = 0;
	tmp = g_data.token;
	if (help_export(&tmp, &i, redir) == 0)
		return (0);
	if (main_export(content, new_env, tmp, i) == 1)
		return (1);
	return (1);
}