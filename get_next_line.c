#include "get_next_line.h"

/*
	NAME
		get_next_line
	SYNOPSIS
		#include "get_next_line.h"
	PROTOTYPE
		char *get_next_line(int fd);
	DESCRIPTION:
		Reads a line from file descriptor fd.
		Uses static buffer to maintain state between calls.
		Buffer size defined by BUFFER_SIZE macro.
	RETURN VALUE
		Next line (including \n) or NULL on EOF/error.
	EXTERNAL FUNC(S)
		read, malloc, free

*/

size_t	get_append_len(char *buf, const char *nlp, size_t line_len, size_t bytes_read)
{
	size_t append_len;

	if (nlp)
		append_len = nlp - buf + 1;
	else
		append_len = bytes_read;
	if (SIZE_MAX - line_len < append_len)
		append_len = SIZE_MAX - line_len;
	return(append_len);
}

char	*append_line(char *line, char *buf, const char *nlp, size_t bytes_read)
{
	static size_t	line_len;
	static size_t	capacity;
	size_t			append_len;

	append_len = get_append_len(buf, nlp, line_len, bytes_read);
	line = ft_realloc(line, line_len, append_len, &capacity);
	if (!line)
		return NULL;
	ft_memcpy(line + line_len, buf, append_len);
	line_len += append_len;
	line[line_len] = 0;
	if (nlp)
	{
		capacity = 0;
		line_len = 0;
	}
	return (line);
}

char *get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static size_t	bytes_read;
	char			*nlp;
	char			*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	nlp = NULL;
	while (!nlp)
	{
		if (bytes_read == 0)
		{
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read < 1)
				return (line);
		}
		nlp = ft_memchr(buf, '\n', bytes_read);
		line = append_line(line, buf, nlp, bytes_read);
		if (!line)
			return NULL;
		if (!nlp)
			bytes_read = 0;
	}
	bytes_read -= nlp - buf + 1;
	ft_memmove(buf, nlp + 1, bytes_read);
	return (line);
}