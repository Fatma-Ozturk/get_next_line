/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faozturk <faozturk@42kocaeli.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:46:45 by faozturk          #+#    #+#             */
/*   Updated: 2022/02/28 14:52:05 by faozturk         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*str[9999]; // fd burada a????lan dosyalar??m??z olacak. 9999 tane dosya a??abiliriz.
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = reading(fd, str[fd]); // fd1 i g??nderirsek onu okuyacak.
	if (!str[fd])
		return (NULL);
	output = line(str[fd]);
	str[fd] = newstr(str[fd]);
	return (output);
}
// fd ler ile i??lem yapmak istedi??imiz text dosyas??n?? belirleyip ona g??re istedi??imiz i??lemi yapabiliyoruz
int main()
{
	int 	fd1 = open("test1", O_RDONLY); // read only
	int 	fd2 = open("test2", O_RDONLY); // read only
	int 	res = open("result", O_WRONLY); // write only
	char	*line;
	
	//printf("fd1'nin de??eri = %d\n",fd1);
	//printf("fd2'nin de??eri = %d\n",fd2);
	//printf("res'nin de??eri = %d\n",res);

	line = get_next_line(fd1);
	write(res, line, ft_strlen(line));  // res e line dakini yaz line uzunlu??u kadar
	
	line = get_next_line(fd2);
	write(res, line, ft_strlen(line));  // 2.kere yazacak bu sefer text2dekini. b??ylecek reste test1 ve test2 dosyalar??nda yazanlar yaz??lm???? olacak.
}

// bu bir ??rnek mainde istedi??imiz ba??ka i??lemleri de yapt??rabiliriz
