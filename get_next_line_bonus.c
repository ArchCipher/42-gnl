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

/*
READ RETURN VALUES
ssize_t
Number of bytes read (≥ 0)
0 on EOF
-1 on error
*/

char	*append_line(char *line, size_t *line_len, char *buf, size_t append_len)
{
	ft_memcpy(line + *line_len, buf, append_len);
	*line_len += append_len;
	line[*line_len] = '\0';
	return (line);
}

size_t	calculate_new_capacity(size_t line_len, size_t append_len, char *buf)
{
	if (line_len + append_len + 1 < SIZE_MAX / 2 && buf[append_len] != '\n')
		return ((line_len + append_len) * 2 + 1);
	return (line_len + append_len + 1);
}

ssize_t	get_append_len(int fd, char *buf)
{
	ssize_t	bytes_read;

	if (buf[0] != 0)
		bytes_read = ft_strlen(buf);
	else
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 1)
			return (bytes_read);
		else if (bytes_read < BUFFER_SIZE)
			buf[bytes_read] = 0;
	}
	return (find_nl(buf, bytes_read));
}

char *get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	char			*line;
	size_t			line_len;
	size_t			capacity;
	size_t			append_len;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = NULL;
	line_len = 0;
	capacity = 0;
	while (1)
	{
		append_len = get_append_len(fd, buf);
		if (append_len < 1)
			return (line);
		if (capacity < line_len + append_len + 1)
		{
			capacity = calculate_new_capacity(line_len, append_len, buf);
			line = ft_realloc(line, line_len, capacity);
			if (!line)
				return (NULL);
		}
		line = append_line(line, &line_len, buf, append_len);
		if (BUFFER_SIZE == append_len)
			buf[0] = 0;
		else
		{
			ft_memmove(buf, buf + append_len, BUFFER_SIZE - append_len);
			buf[BUFFER_SIZE - append_len] = '\0';
		}
		if (line[line_len - 1] == '\n')
			break ;
	}
	return (line);
}
