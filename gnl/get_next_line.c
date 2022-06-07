/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faozturk <faozturk@42kocaeli.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:12:40 by faozturk          #+#    #+#             */
/*   Updated: 2022/02/27 16:30:41 by faozturk         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*reading(int fd, char *str)
{
	char	*tmp;
	int		readbytes;

	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	readbytes = 1;
	while (!ft_strchr(str, '\n') && readbytes != 0)
	{
		readbytes = read(fd, tmp, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[readbytes] = '\0';
		str = ft_strjoin(str, tmp);
	}
	free(tmp);
	return (str);
}

char	*line(char *str)
{
	int		i;
	char	*fresh;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	fresh = (char *)malloc(sizeof(char) * (i + 2));
	if (!fresh)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		fresh[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		fresh[i] = str[i];
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}

char	*newstr(char *str)
{
	int		a;
	int		b;
	char	*newstr;

	a = 0;
	while (str[a] && str[a] != '\n')
		a++;
	if (!str[a])
	{
		free(str);
		return (NULL);
	}
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(str) - a + 1));
	if (!newstr)
		return (NULL);
	a++;
	b = 0;
	while (str[a])
		newstr[b++] = str[a++];
	newstr[b] = '\0';
	free(str);
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = reading(fd, str);
	if (!str)
		return (NULL);
	output = line(str);
	str = newstr(str);
	return (output);
}
