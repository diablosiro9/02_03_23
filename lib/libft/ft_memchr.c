/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mla-rosa <mla-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:15:51 by mla-rosa          #+#    #+#             */
/*   Updated: 2021/11/29 11:45:29 by mla-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*stmp;

	i = 0;
	stmp = (char *)s;
	while (i < n)
	{
		if (stmp[i] == (char)c)
			return ((void *)&stmp[i]);
		i++;
	}
	return (NULL);
}
