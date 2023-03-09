/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mla-rosa <mla-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:22:54 by mla-rosa          #+#    #+#             */
/*   Updated: 2021/10/29 13:18:21 by mla-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*tmp1;
	const char	*tmp2;

	i = 0;
	tmp1 = (const char *)s1;
	tmp2 = (const char *)s2;
	if (s1 == s2 || n == 0)
		return (0);
	while (i < (n - 1) && tmp1[i] == tmp2[i])
		i++;
	return ((unsigned char)tmp1[i] - (unsigned char)tmp2[i]);
}
