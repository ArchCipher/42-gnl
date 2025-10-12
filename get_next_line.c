#include "get_next_line.h"
#include <stdio.h>

size_t	ft_astrlen(const char *buf, size_t bytes_read)
{
	char *ebp;

	ebp = ft_memchr(buf, '\n', bytes_read);
	if (ebp)
		return (ebp - buf + 1);
	return (bytes_read);
}

char	*append_line(char *line, size_t line_len, const char *buf, size_t append_len)
{
	char	*elp;

	if (!buf)
		return NULL;
	if (append_len == 0)
		return NULL;
	if (line_len == 0)
	{
		line = malloc(append_len + 1);
		if (!line)
			return (NULL);
		line[append_len] = 0;
		line = ft_memcpy(line, buf, append_len);
		return (line);
	}
	line = ft_realloc(line, line_len, line_len + append_len + 1);
	if (!line)
		return (NULL);
	line[line_len + append_len] = 0;
	elp = line + line_len;
	elp = ft_memcpy(elp, buf, append_len);
	return (line);
}

char *get_next_line(int fd)
{
	static size_t		bytes_read;
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	size_t		append_len;
	size_t		line_len;

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
		buf[bytes_read] = 0;
		append_len = ft_astrlen(buf, bytes_read); 
		line = append_line(line, line_len, buf, append_len);
		if (!line)
			return (NULL);
		line_len += append_len;
		if (line[line_len - 1] == '\n' && bytes_read > append_len)
		{
			ft_memmove(buf, buf + append_len, bytes_read - append_len);
			bytes_read -= append_len;
			break;
		}
		else
			buf[0] = 0;
	}
	return (line);
}
