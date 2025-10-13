#include "get_next_line.h"

/*
	GET_NEXT_LINE
	Reads from the file descriptor to get the next first line. The function
	reads BUFFER_SIZE characters at a time and appends the characters to the
	return line. It only appends the characters until it meets a newline or the
	end of file is reached. The remaining characters stay in the buffer for the
	next call of get_next_line. If a newline is already present in the initial
	buffer, no additional characters are read.
	PARAMETER(S)
		File descriptor to read from
	RETURN
	The function returns the next line read from the file descriptor as a
	string. If there is nothing left to be read or if an error occurred, it
	returns NULL.
*/

size_t	get_append_len(char *buf, const char *ebp, size_t bytes_read)
{
	if (ebp)
		return(ebp - buf + 1);
	return(bytes_read);
}

size_t	check_overflow(size_t line_len, size_t append_len)
{
	size_t malloc_len;

	if (SIZE_MAX - line_len <= append_len)
		return (SIZE_MAX - 1);
	malloc_len = line_len + append_len;
	if (malloc_len < (SIZE_MAX / 2) - 1)
		malloc_len *= 2;
	return (malloc_len);
}

char	*append_line(char *line, char *buf, size_t *line_len, size_t append_len)
{
	if (SIZE_MAX - *line_len <= append_len)
		append_len = SIZE_MAX - *line_len - 1;
	line = ft_realloc(line, *line_len, check_overflow(*line_len, append_len) + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line + *line_len, buf, append_len);
	*line_len += append_len;
	line[*line_len] = 0;
	return (line);
}

char *get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	char			*ebp;
	char			*line;
	size_t			line_len;
	size_t			bytes_read;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	ebp = NULL;
	line_len = 0;
	while (!ebp)
	{
		if (buf[0] == 0)
		{
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read < 1)
				return (line);
			ebp = ft_memchr(buf, '\n', bytes_read);
		}
		else
			ebp = ft_memchr(buf, '\0', BUFFER_SIZE);
		line = append_line(line, buf, &line_len, get_append_len(buf, ebp, bytes_read));
		buf[0] = 0;
	}
	if (ebp)
		ft_memmove(buf, ebp + 1, (bytes_read - (ebp - buf + 1)));
	return (line);
}

	if (ebp)
		return (buf - ebp);
	else
		return(BUFFER_SIZE);