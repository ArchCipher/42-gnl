/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:57:37 by kmurugan          #+#    #+#             */
/*   Updated: 2025/10/21 19:54:27 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static ssize_t	get_append_len(int fd, char *buf);
static char		*grow_line(char *line, size_t line_len, ssize_t append_len,
					size_t *capacity);
static char		*append_line(char *line, size_t *line_len, char *buf,
					ssize_t append_len);

/*
	NAME
		get_next_line
	SYNOPSIS
		#include "get_next_line_bonus.h"
	PROTOTYPE
		char *get_next_line(int fd);
	DESCRIPTION:
		Reads a line from file descriptor using a static buffer to maintain state
		between calls. The buffer size can be defined by the BUFFER_SIZE macro
		during compilation.
	RETURN VALUE
		Returns the next line (including \n) or NULL on EOF/error.
	EXTERNAL FUNC(S)
		read, malloc, free
*/

char	*get_next_line(int fd)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE];
	char		*line;
	size_t		line_len;
	size_t		capacity;
	ssize_t		append_len;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	line = NULL;
	line_len = 0;
	capacity = 0;
	while (1)
	{
		append_len = get_append_len(fd, buf[fd]);
		if (append_len < 1)
			return (line);
		line = grow_line(line, line_len, append_len, &capacity);
		if (!line)
			return (NULL);
		line = append_line(line, &line_len, buf[fd], append_len);
		if (line[line_len - 1] == '\n')
			return (line);
	}
}

/*
	DESCRIPTION
		Reads from fd if buffer empty and returns bytes to append up to new line
		or upto end of buffer or EOF. Returns -1 on read error, 0 on EOF.
*/

static ssize_t	get_append_len(int fd, char *buf)
{
	ssize_t	bytes_read;
	char	*nl_pos;

	bytes_read = ft_strlen(buf);
	if (!bytes_read)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 1)
			return (bytes_read);
		if (bytes_read < BUFFER_SIZE)
			buf[bytes_read] = 0;
	}
	nl_pos = ft_memchr(buf, '\n', bytes_read);
	if (!nl_pos)
		return (bytes_read);
	return (nl_pos - buf + 1);
}

/*
DESCRIPTION
	Reallocates the line to a new capacity and returns a pointer to the
	new line, or NULL if the allocation fails. Returns the original line if the
	capacity is sufficient.
*/

static char	*grow_line(char *src, size_t src_len, ssize_t append_len,
		size_t *capacity)
{
	char	*dst;
	size_t	needed_capacity;

	if (*capacity >= src_len + append_len + 1)
		return (src);
	needed_capacity = src_len + append_len + 1;
	if ((*capacity < SIZE_MAX / 2) && (*capacity * 2 >= needed_capacity))
		*capacity *= 2;
	else
		*capacity = needed_capacity;
	dst = malloc(*capacity);
	if (!dst)
	{
		free(src);
		return (NULL);
	}
	if (src)
		ft_memcpy(dst, src, src_len);
	free(src);
	return (dst);
}

/*
DESCRIPTION
	Appends the bytes from the buffer to the line and returns a pointer to the
	new line, or NULL if the allocation fails or if line is NULL.
*/

static char	*append_line(char *line, size_t *line_len, char *buf,
		ssize_t append_len)
{
	ft_memcpy(line + *line_len, buf, append_len);
	*line_len += append_len;
	line[*line_len] = '\0';
	if (BUFFER_SIZE > append_len)
		ft_memcpy(buf, buf + append_len, BUFFER_SIZE - append_len);
	buf[BUFFER_SIZE - append_len] = 0;
	return (line);
}
