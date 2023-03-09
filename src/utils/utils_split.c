/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:01:39 by dojannin          #+#    #+#             */
/*   Updated: 2023/02/18 17:10:09 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

int	ft_check_c(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

int	count_char_c(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_check_c(s[i], c) == 1)
			i++;
		if (s[i] && ft_check_c(s[i], c) == 0)
		{
			count++;
			while (s[i] && ft_check_c(s[i], c) == 0)
				i++;
		}
	}
	return (count);
}

char	*ft_alloc_str(char const *s, char c)
{
	char	*tab;
	int		i;

	i = 0;
	while (s[i] && ft_check_c(s[i], c) == 0)
		i++;
	tab = malloc(sizeof(char) * (i + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s[i] && ft_check_c(s[i], c) == 0)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_oldsplit(char const *s, char c)
{
	int		i;
	int		nb_c;
	char	**dst;

	i = 0;
	if (s == NULL)
		return (NULL);
	nb_c = count_char_c(s, c);
	dst = (char **)malloc(sizeof(char *) * (nb_c + 1));
	if (dst == NULL)
		return (NULL);
	nb_c = 0;
	while (s[i])
	{
		while (s[i] && ft_check_c(s[i], c) == 1)
			i++;
		if (s[i] && ft_check_c(s[i], c) == 0)
		{
			dst[nb_c] = ft_alloc_str((s + i), c);
			nb_c++;
			while (s[i] && ft_check_c(s[i], c) == 0)
				i++;
		}
	}
	dst[nb_c] = NULL;
	return (dst);
}

char	*ft_strjoin_bis(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	i = -1;
	j = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (size));
	if (str == NULL)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}