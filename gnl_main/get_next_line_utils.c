/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faozturk <faozturk@42kocaeli.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:33:08 by faozturk          #+#    #+#             */
/*   Updated: 2022/02/27 16:44:43 by faozturk         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	c;

	c = 0;
	if (!s)
		return (0);
	while (s[c] != 0)
		c++;
	return (c);
}

char	*ft_strjoin(char *str, char *tmp)
{
	char	*new;
	size_t	i;
	size_t	a;

	if (!str)
	{
		str = (char *)malloc(1 * sizeof(char));
		str[0] = '\0';
	}
	if (!str || !tmp)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(tmp) + 1));
	if (new == NULL)
		return (NULL);
	i = -1;
	a = 0;
	while (str[++i])
		new[i] = str[i];
	while (tmp[a])
		new[i++] = tmp[a++];
	new[i] = '\0';
	free(str);
	return (new);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (0);
}
