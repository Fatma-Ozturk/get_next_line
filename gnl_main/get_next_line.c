/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faozturk <faozturk@42kocaeli.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:12:40 by faozturk          #+#    #+#             */
/*   Updated: 2022/02/28 15:55:40 by faozturk         ###   ########.tr       */
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

// BUFFER_SIZE + 1 tane geçici bir alan oluşturuyoruz.
// readbytes burada okunan byte sayısını verecek. 1 den başlatıyoruz çünkü while döngüsü başlayabilsin, yani 0 dan büyük olduğu sürece hangi değerden başlattığımızın bir önemi yok.
// read fonksiyonuna gönderip tmp yi BUFFER_SIZE kadar oku kaç byte okuduğunu readbyte olarak ver diyoruz. Her zaman BUFFER_SIZE kadar okunacak byte olmayabilir. Daha az varsa readbytes daha küçük olacak mesela.
// readbytesın -1 olması durumubir hata durumunda oluşur. Onun kontrolünü yapıyoruz.İşlem yapılacak bir text dosyası yoksa.
// tmp sonuna null koyup str ile birleştiriyoruz. Str ilk başta boş döngü devam ettikçe sonuna eklenecektir.
// free tmp ile oluşturduğumuz alanı boşaltıyoruz.
// mesela ilk satır "Merhaba, ben Fatma(\n)" ikinci satır "Nasılsın?(\n)" olsun. BUFFER_SIZE = 7 olsun. 3 kere döngüye girecek (Merhaba)(, ben F)(atma\nNa) sonuncuda içinde \n görünce çıkacak. yani str artık Merhaba, ben Fatma\nNa olacak.
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

// Bu fonksiyonda sonundaki Na yani alt satırdan eklenen kısım olmadan yeni bir string oluşturuyoruz. i yi \n görene kadar arttırıyoruz.
// fresh stringine i + 2 tane (null ve \n ekleyip) yer açıyoruz.
// str dekileri freshe atıp sonuna \n ekliyoruz ve en son '\0' koyup bitiriyoruz.
// fresh stringi artık sadece ilk satırı verecek.

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
// Burada strnin içinde kestiğimiz Na yı yani 2. satırdan gelen kısmı yeni str miz olarak belirliyoruz. Böylece fonksiyonu tekrar çağırıp 2. satırı yazdırmak istersek str Na dan başlamış olacak.
// indeksi yine \n e kadar getiriyoruz.kırpılmamış str uzunluğundan ilk satırı çıkartıyoruz elimizde Na kalıyor ve +1 null ekleyip yer tahsis ediyoruz.
// a yı bir tane daha arttırıyoruz ki \n i atlasın.
// strdeki a dan sonraki kısmı newstrye aktarıyoruz.
// boşa çıkan stryi freeleyip. newstryi döndürüyoruz.

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

// str yi reading fonksiyonuna gönderip okuma işlemini gerçekleştiriyoruz.
// line fonksiyonu ile sadece ilk satırı aldık.
// str yi artık newstr fonksiyonu ile güncelledik. İkinci satırdan eklenen fazla kısımla.
// output yani ilk satırı döndürdük.


int	main()
{
	int	fd = open("text", O_RDONLY); //open for read only txt yi açıp içini okuyacak.
	char	*line = get_next_line(fd); // line içine output u attı.

	printf("%s", line);
	line = get_next_line(fd); // 2 .kez çalıştırdığımız için 2. satırı da verecek.
	printf("%s", line);
}
