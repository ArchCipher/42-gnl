#include "get_next_line_bonus.h"

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

char	*get_append_len(size_t line_len, char *buf, char **buf_pos, size_t bytes_read)
{
	char	*nlp;

	nlp = ft_memchr((buf + **buf_pos), '\n', bytes_read);
	if (!nlp)
		nlp = buf + bytes_read;
	if (nlp - buf_pos > (SIZE_MAX - line_len - 1))
		return (SIZE_MAX - line_len - 1);
	return(nlp - *buf_pos);
}

char	*append_line(char *line, size_t *line_len, char *buf, char **buf_pos, size_t bytes_read)
{
	char	*nlp;
	size_t	new_line_len;
	size_t append_len;

	append_len = get_append_len(line_len, buf, buf_pos, bytes_read);
	line = ft_realloc(line, line_len, append_len + 1);
	if (!line)
		return NULL;
	ft_memcpy(line + *line_len, buf, append_len);
	*line_len += append_len;
	line[*line_len] = 0;
	return (line);
}

char *get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static char		*buf_pos;
	size_t			bytes_read;
	size_t			line_len;
	char			*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	if (buf_pos == NULL)
		buf_pos = buf;
	line_len = 0;
	bytes_read = 0;
	while (1)
	{
		if (buf_pos = buf + bytes_read)
		{
			bytes_read = read_file(fd, buf, BUFFER_SIZE);
			if (bytes_read < 0)
				return (NULL);
			buf_pos = buf;
		}
		line = append_line(line, &line_len, buf, &buf_pos, &bytes_read);
		if (line_len == 0 || line_len == SIZE_MAX - 1)
			break;
	}
	return (line);
}