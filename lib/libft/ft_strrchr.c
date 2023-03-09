/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:04:49 by mla-rosa          #+#    #+#             */
/*   Updated: 2023/03/04 15:34:12 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_slen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strrchr(char *s, int c)
{
	int		i;

	i = ft_slen(s);
	if ((char)c == '\0')
		return ((char *)s + i);
	while (i--)
		if (s[i] == (char)c)
			return ((char *)s + i);
	return (NULL);
}
