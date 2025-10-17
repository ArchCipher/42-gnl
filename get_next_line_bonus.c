#include "get_next_line_bonus.h"
#include <stdio.h>

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

size_t	get_append_len(char *buf, size_t line_len, ssize_t valid_bytes)
{
	size_t	append_len;
	char	*nl_ptr;

	nl_ptr = ft_memchr(buf, '\n', valid_bytes);
	if (nl_ptr)
		append_len = nl_ptr - buf + 1;
	else
		append_len = valid_bytes;
	if (SIZE_MAX - line_len - 1 < append_len)
		append_len = SIZE_MAX - line_len - 1;
	return(append_len);
}

// ssize_t	fill_buffer(int fd, char *buf, size_t *buf_len)
// {
// 	ssize_t	read_bytes;

// 	read_bytes = read(fd, buf + *buf_len, BUFFER_SIZE - *buf_len);
// 	if (read_bytes > 0)
// 		*buf_len += read_bytes;
// 	return (read_bytes);
// }

size_t	fill_buffer(int fd, char *buf)
{
	size_t	valid_bytes;
	ssize_t	bytes_read;
	char	*buf_ptr;
	char	*nl_ptr;

	if (buf[0] == 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (0);
		else if (bytes_read < BUFFER_SIZE)
			buf[bytes_read] = 0;
		return (bytes_read);
	}
	buf_ptr = ft_memchr(buf, '\0', BUFFER_SIZE);
	valid_bytes = buf_ptr - buf;
	nl_ptr = ft_memchr(buf, '\n', valid_bytes);
	if (nl_ptr)
		return (valid_bytes);
	bytes_read = read(fd, buf + valid_bytes, BUFFER_SIZE - valid_bytes);
	valid_bytes += bytes_read;
	if (valid_bytes != BUFFER_SIZE)
		buf[valid_bytes] = 0;
	return (valid_bytes);
}

char	*append_line(char *line, size_t line_len, char *buf, size_t append_len)
{
	ft_memcpy(line + line_len, buf, append_len);
	line[line_len + append_len] = 0;
	return (line);
}

char *get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	char			*line;
	size_t			line_len;
	size_t			capacity;
	size_t			append_len;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	line_len = 0;
	capacity = 0;
	append_len = 0;
	while (1)
	{
		append_len = get_append_len(buf, line_len, fill_buffer(fd, buf));
		if (append_len < 1)
			return (line);
		if (capacity < line_len + append_len + 1)
		{
			if (line_len + append_len + 1 < SIZE_MAX / 2 && buf[append_len] != '\n')
				capacity = (line_len + append_len) * 2 + 1;
			else
				capacity = line_len + append_len + 1;
			line = ft_realloc(line, line_len, capacity);
			if (!line)
				return (NULL);
		}
		line = append_line(line, line_len, buf, append_len);
		line_len += append_len;
		if (BUFFER_SIZE == append_len)
			buf[0] = 0;
		else
		{
			ft_memmove(buf, buf + append_len, BUFFER_SIZE - append_len);
			buf[BUFFER_SIZE - append_len] = 0;
		}
		if (line[line_len - 1] == '\n')
			break ;
	}
	return (line);
}
