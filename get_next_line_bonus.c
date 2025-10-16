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

// char	*get_append_len(size_t line_len, char *buf, char **buf_pos, size_t bytes_read)
// {
// 	char	*nlp;

// 	nlp = ft_memchr((buf + **buf_pos), '\n', bytes_read);
// 	if (!nlp)
// 		nlp = buf + bytes_read;
// 	if (nlp - buf_pos > (SIZE_MAX - line_len - 1))
// 		return (SIZE_MAX - line_len - 1);
// 	return(nlp - *buf_pos);
// }

char *get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 2];
	char		*line;
	char		*l_ptr;
	ssize_t		append_len;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	l_ptr = NULL;
	while (1) // (line[l_ptr - line] == '\n') // || l_ptr != '\0' // || line_len == SSIZE_MAX - 1
	{
		if (buf[BUFFER_SIZE] == 0)
			append_len = read_file(fd, buf);
		else
			append_len = get_append_len(buf, line, l_ptr);
		if (append_len < 1)
			return (line);
		line = ft_realloc(line, &l_ptr, append_len);
		if (!line || !l_ptr)
			return (NULL);
		l_ptr = append_line(l_ptr, buf, append_len);
		if (l_ptr - 1 == '\n')
			break;
	}
	return (line);
}

size_t	read_file(int fd, char *buf)
{
	ssize_t	nbyte;
	ssize_t	rbyte;
	char	*tbyte;
	char	*nl_ptr;

	nbyte = 256;
	tbyte = buf;
	nl_ptr = NULL;
	if (nbyte > BUFFER_SIZE)
		nbyte = BUFFER_SIZE;
	while (tbyte - buf < BUFFER_SIZE && !nl_ptr)
	{
		buf[BUFFER_SIZE] = 0;
		rbyte = read(fd, tbyte, nbyte);
		if (rbyte < 1)
			return (rbyte);
		nl_ptr = ft_memchr(tbyte, '\n', rbyte);
		tbyte += rbyte;
	}
	if (!nl_ptr)
		return(tbyte - buf);
	buf[BUFFER_SIZE] = (unsigned char)(tbyte - (nl_ptr + 1));
	buf[BUFFER_SIZE + 1] = (unsigned char)((tbyte - buf) / 255);
	return ((nl_ptr + 1) - buf);
}

size_t	get_append_len(char *buf, char *line, char *l_ptr)
{
	ssize_t	rem_byte;
	ssize_t	nbyte;
	char	*tbyte;
	char	*nl_ptr;

	nbyte = 256;
	rem_byte = (unsigned char) buf[BUFFER_SIZE];
	tbyte = buf + ((unsigned char) buf[BUFFER_SIZE + 1] * nbyte);
	nl_ptr = ft_memchr(tbyte - rem_byte, '\n', rem_byte);
	if (!nl_ptr)
		return (rem_byte);
	buf[BUFFER_SIZE] = (unsigned char)(tbyte - (nl_ptr + 1));
	buf[BUFFER_SIZE + 1] = (unsigned char)((tbyte - buf) / 255);
	return ((nl_ptr + 1) - buf);
}

char	*append_line(char *l_ptr, char *buf, ssize_t append_len)
{
	ft_memcpy(l_ptr, buf, append_len);
	l_ptr += append_len;
	l_ptr = 0;
	return (l_ptr);
}