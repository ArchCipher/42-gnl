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

/*
READ RETURN VALUES
ssize_t
Number of bytes read (≥ 0)
0 on EOF
-1 on error
*/

ssize_t	get_append_len(char *buf, const char *nlp, ssize_t line_len, ssize_t bytes_read)
{
	ssize_t append_len;

	if (nlp)
		append_len = nlp - buf + 1;
	else
		append_len = bytes_read;
	if (SSIZE_MAX - line_len < append_len)
		append_len = SSIZE_MAX - line_len;
	return(append_len);
}

char	*append_line(char *line, char *buf, const char *nlp, ssize_t bytes_read)
{
	static ssize_t	line_len;
	static ssize_t	capacity;
	ssize_t			append_len;

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
	static ssize_t	bytes_read;
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


// char *get_next_line(int fd)
// {
// 	static char		buf[BUFFER_SIZE];
// 	static char		*buf_pos;
// 	size_t			bytes_read;
// 	size_t			line_len;
// 	char			*line;

// 	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
// 		return (NULL);
// 	line = NULL;
// 	if (buf_pos == NULL)
// 		buf_pos = buf;
// 	line_len = 0;
// 	bytes_read = 0;
// 	while (1)
// 	{
// 		if (buf_pos = buf + bytes_read)
// 		{
// 			bytes_read = read_file(fd, buf, BUFFER_SIZE);
// 			if (bytes_read < 0)
// 				return (NULL);
// 			buf_pos = buf;
// 		}
// 		line = append_line(line, &line_len, buf, &buf_pos, &bytes_read);
// 		if (line_len == 0 || line_len == SIZE_MAX - 1)
// 			break;
// 	}
// 	return (line);
// }