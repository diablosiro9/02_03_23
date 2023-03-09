/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:15:00 by mla-rosa          #+#    #+#             */
/*   Updated: 2023/02/20 13:53:21 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;
	size_t			len_s;

	len_s = ft_strlen((char *)s);
	if (start > len_s)
	{
		str = malloc(sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (start + len > len_s)
		len = len_s - start;
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	start -= 1;
	while (++i < len && s[++start])
		str[i] = s[start];
	str[i] = '\0';
	return (str);
}
