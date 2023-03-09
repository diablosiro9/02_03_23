/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:21:13 by imac21            #+#    #+#             */
/*   Updated: 2023/03/03 17:08:50 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"


int	ft_isquote(int c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

int	ft_isequal(int c)
{
	if (c == '=')
		return (1);
	return (0);
}

int	ft_iswspace(char c)
{
	while (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

// int	skip_echo(int *o, int *i, t_token **tmp, int redir)
// {
// 	while (*i < ft_strlen("echo"))
// 		*i += 1;
// 	if (!g_data.token)
// 	{
// 		ft_putchar_fd('\n', redir);
// 		return (1);
// 	}
// 	while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) == 1)
// 		*i += 1;
// 	if ((*tmp)->next)
// 		(*tmp) = (*tmp)->next;
// 	while (!ft_strncmp((*tmp)->token->value, "-n", ft_strlen("-n")))
// 	{
// 		(*tmp) = (*tmp)->next;
// 		*o = 1;
// 		while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) != 1)
// 			*i += 1;
// 		while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) == 1)
// 			*i += 1;
// 	}
// 	return (0);
// }

int	case_quote(char *cmd, t_token **tmp, int *i, int redir)
{
	while ((*tmp) && ft_isquote((*tmp)->value[0]) == 1)
	{
		ft_putstr_fd((*tmp)->value, redir);
		if ((*tmp)->next)
			(*tmp) = (*tmp)->next;
	}
	while (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		*i += 1;
	while (cmd[*i] && ft_isquote(cmd[*i]) != 1)
		*i += 1;
	while (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		*i += 1;
	ft_putstr_fd((*tmp)->value, redir);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	while ((*tmp) && ft_isquote((*tmp)->value[0]) == 1)
	{
		ft_putstr_fd((*tmp)->value, redir);
		if ((*tmp)->next)
			(*tmp) = (*tmp)->next;
		else
			return (1);
	}
	return (0);
}

int	case_string(char *cmd, t_token **tmp, int *i, int redir)
{
	int	idx = 0;
	while ((*tmp)->value[idx] && ft_iswspace((*tmp)->value[idx]) != 1)
		ft_putchar_fd((*tmp)->value[idx++], redir);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	else
		return (1);
	while (cmd[*i] && ft_isquote(cmd[*i]) != 1 && ft_iswspace(cmd[*i]) != 1
		&& ft_isprint(cmd[*i]) > 1 && cmd[*i] != '=')
		*i += 1;
	if (cmd[*i] == '=')
		*i += 1;
	return (0);
}

int	main_echo(char *cmd, t_token **tmp, int *i, int redir, int *flag)
{
	if (*flag == -1)
		(*tmp) = (*tmp)->next;
	printf("t_type = %d\n",(*tmp)->t_type );
	while (cmd[*i] && (*tmp) && (*tmp)->t_type != 5)
	{
		if (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		{
			if (case_quote(cmd, tmp, i, redir) == 1)
				return (1);
		}
		else if (cmd[*i] && ft_iswspace(cmd[*i]) == 1)
		{
			if ((*tmp)->t_type != 7)
				ft_putchar_fd(' ', redir);
			*i += 1;
			while (cmd[*i] && ft_iswspace(cmd[*i]) == 1)
				*i += 1;
		}
		else if (cmd[*i] && ft_iswspace(cmd[*i]) != 1)
		{
			if (case_string(cmd, tmp, i, redir) == 1)
				return (1);
		}
		
        // printf("milieu loop\n");
    }
	// if ((*tmp)->t_type == 6)
	// {
	// 	ft_putstr_fd()
	// }
    // printf("fin loop\n");
	return (0);
}

// int	checking_full_n()
// {
	
// }

void	help_echo(t_token *tmp, int *i, int *flag)
{
	if (ft_strlen(tmp->value) == 3 && tmp->value[ft_strlen(tmp->value) - 1] == ' ')
	{
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			*flag = 2;
			return ;
		}
		*flag = -1;
	}
	if (ft_strlen(tmp->value) > 3)
		return ;
	// if (checking_full_n() == 1)
	// 	return ;
	while (!ft_strncmp(tmp->value, "-n", ft_strlen("-n")))
	{
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			*flag = 2;
			return ;
		}
		*flag = -1;
		while (g_data.cmd[*i] && ft_iswspace(g_data.cmd[*i]) != 1)
			*i += 1;
		while (g_data.cmd[*i] && ft_iswspace(g_data.cmd[*i]) == 1)
			*i += 1;
	}
	(void)flag;
}
	

int	ft_echo(int redir)
{
	t_token 	*tmp;
	char		*cmd;
	int			i;
	int			flag;

	flag = 1;
	i = 0;
	tmp = g_data.token;
    cmd = g_data.cmd;
	if (redir == -1)
		redir = 1;
    while (i < ft_strlen("echo"))
		i += 1;
	while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) == 1)
		i += 1;
	if (tmp->next)
		tmp = tmp->next;
	help_echo(tmp, &i, &flag);
	if (flag == 2)
		return (1);
	main_echo(cmd, &tmp, &i, redir, &flag);
	if (flag == 1)
		ft_putchar_fd('\n', redir);
	return (1);
}