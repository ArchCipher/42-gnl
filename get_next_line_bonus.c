/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:57:37 by kmurugan          #+#    #+#             */
/*   Updated: 2025/10/18 14:33:06 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*line;
	size_t		line_len;
	size_t		capacity;
	size_t		append_len;

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
			return (line);
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	size_t		len;
	char		*line;
	ssize_t		r;
	size_t		n;
	size_t		cap;
	if (!buf[0])
		r = read(fd, buf, BUFFER_SIZE);
		if (r <= 0)
		return (line);
	n = 0;
	while (buf[n] && buf[n] != '\n')
		n++;
	if (buf[n] == '\n')
		n++;
	if (len + n + 1 > cap)
	{
		cap = (len + n) * 2 + 1;
		line = ft_realloc(line, len, cap);
		if (!line)
			return (NULL);
	}
	ft_memcpy(line + len, buf, n);
	len += n;
	line[len] = 0;
	ft_memmove(buf, buf + n, BUFFER_SIZE - n);
	buf[BUFFER_SIZE - n] = 0;
	if (line[len - 1] == '\n' || !buf[0])
		return (line);
}
// if (!buf[0] && (r = read(fd, buf, BUFFER_SIZE)) <= 0)
// 	return (line);
// n = 0;
// while (buf[n] && buf[n] != '\n')
// 	n++;
// if (buf[n] == '\n')
// 	n++;
// if (len + n + 1 > cap)
// {
// 	cap = (len + n) * 2 + 1;
// 	line = ft_realloc(line, len, cap);
// 	if (!line)
// 		return (NULL);
// }
// ft_memcpy(line + len, buf, n);
// len += n;
// line[len] = 0;
// ft_memmove(buf, buf + n, BUFFER_SIZE - n);
// buf[BUFFER_SIZE - n] = 0;
// if (line[len - 1] == '\n' || !buf[0])
// 	return (line);