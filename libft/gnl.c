//
// Created by Professional on 20.09.2020.
//

#include "libft.h"

int		buffer_handler(char **buffer, char **line)
{
	char	*start;
	char	*sub;
	int		len;
	int		sub_len;
	int		buf_len;

	buf_len = ft_strlen(*buffer);
	sub_len = 0;
	if (*buffer && buf_len > 0)
	{
		start = ft_strchr(*buffer, '\n');
		if (start)
			sub_len = ft_strlen(start);
		len = buf_len - sub_len;
		sub = ft_strsub(*buffer, 0, len);
		*line = (len == 0 ? ft_strdup("\0") : ft_strdup(sub));
		ft_strdel(&sub);
		if (sub_len > 1)
			sub = ft_strsub(*buffer, len + 1, buf_len);
		ft_strdel(buffer);
		*buffer = sub;
	}
	return (1);
}

int		key_check(int key, char **dscptr)
{
	if (key < 0)
		return (-1);
	else if (key == 0 && !(*dscptr))
	{
		ft_strdel(dscptr);
		return (0);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*dscptr[10245];
	int			key;
	char		*tmp;
	char		buffer[BUFF_SIZE + 1];

	if (fd < 0 || !line || fd > 10240 || BUFF_SIZE <= 0)
		return (-1);
	if (dscptr[fd] && ft_strchr(dscptr[fd], '\n'))
		return (buffer_handler(&dscptr[fd], line));
	while ((key = read(fd, &buffer, BUFF_SIZE)) && key > 0)
	{
		if (!dscptr[fd])
			dscptr[fd] = ft_strdup("");
		buffer[key] = '\0';
		tmp = dscptr[fd];
		dscptr[fd] = ft_strjoin(dscptr[fd], buffer);
		ft_strdel(&tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (key <= 0)
		if ((key = key_check(key, &dscptr[fd])) <= 0)
			return (key);
	return (buffer_handler(&dscptr[fd], line));
}