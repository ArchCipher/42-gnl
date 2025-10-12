#include "get_next_line.h"
#include <stdio.h>

size_t	ft_astrlen(const char *buf, size_t bytes_read)
{
	char *ebp;

	if (!buf)
		return 0;
	ebp = ft_memchr(buf, '\n', bytes_read);
	if (ebp)
		return (ebp - buf + 1);
	return (bytes_read);
}

char	*append_line(char *line, size_t old_len, const char *buf, size_t append_len)
{
	char	*elp;

	if (!buf || append_len == 0)
		return NULL;
	if (old_len == 0)
	{
		line = malloc(append_len + 1);
		if (!line)
			return (NULL);
		elp = line;
	}
	else
	{
		line = ft_realloc(line, old_len, old_len + append_len + 1);
		if (!line)
			return (NULL);
		elp = line + old_len;
	}
	elp = ft_memcpy(elp, buf, append_len);
	elp[append_len] = 0;
	return (line);
}



char *get_next_line(int fd)
{
	static size_t	bytes_read;
	static char		buf[BUFFER_SIZE + 1];
	char			*line;
	size_t			append_len;
	size_t			line_len;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return NULL;
	line = NULL;
	line_len = 0;
	while (1)
	{
		if (buf[0] == 0)
		{
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read < 0)
				return NULL;
		}
		append_len = ft_astrlen(buf, bytes_read); 
		line = append_line(line, line_len, buf, append_len);
		if (!line)
			return (NULL);
		line_len += append_len;
		if (bytes_read > append_len)
		{
			ft_memmove(buf, buf + append_len, bytes_read - append_len);
			bytes_read -= append_len;
		}
		else
			buf[0] = 0;
		if (line[line_len - 1] == '\n')
			break;
	}
	return (line);
}
