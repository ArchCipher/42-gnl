#include "get_next_line.h"
#include <stdio.h>

// calculate append_len
size_t	get_append_len(char *buf, const char *ebp, size_t bytes_read)
{
	if (!ebp)
		return(bytes_read);
	return(ebp - buf + 1);
}

char	*append_line(char *line, char *buf, const char *ebp, size_t bytes_read)
{
	size_t			append_len;
	static size_t	line_len;
	size_t			new_len;

	append_len = get_append_len(buf, ebp, bytes_read);
	new_len = line_len + append_len;
	line = ft_realloc(line, line_len, new_len + 1);
	if (!line)
		return NULL;
	ft_memcpy(line + line_len, buf, append_len);
	line_len += append_len;
	if (ebp)
		line_len = 0;
	return (line);
}

char *get_next_line(int fd)
{
	static size_t	bytes_read;
	static char		buf[BUFFER_SIZE];
	char			*ebp;
	char			*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return NULL;
	line = NULL;
	ebp = NULL;
	while (!ebp)
	{
		if (buf[0] == 0)
		{
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read < 0)
				return (NULL);
		}
		ebp = ft_memchr(buf, '\n', bytes_read);
		line = append_line(line, buf, ebp, bytes_read);
		buf[0] = 0;
	}
	bytes_read -= ebp - buf + 1;
	ft_memmove(buf, ebp + 1, bytes_read);
	return (line);
}
