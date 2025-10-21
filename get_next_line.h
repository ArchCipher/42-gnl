/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:27:13 by kmurugan          #+#    #+#             */
/*   Updated: 2025/10/21 19:54:45 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdint.h> // SIZE_MAX
# include <stdlib.h> // malloc, free
# include <unistd.h> // read, ssize_t

#define MAX_STATIC_BUFFER_SIZE 1073741824 // 1GB
// #define	MAX_READ_SIZE			2147479552 // max read() on Linux

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# if BUFFER_SIZE < 1
#  error BUFFER_SIZE too small
# endif

// 2147479552 - max read on Linux but linker fails at this value
# if BUFFER_SIZE > MAX_STATIC_BUFFER_SIZE
#  error BUFFER_SIZE too large for static allocation
# endif

// # if BUFFER_SIZE > MAX_READ_SIZE
// #  error BUFFER_SIZE exceeds read() limit on Linux
// # endif

// get_next_line
char	*get_next_line(int fd);
ssize_t	read_buffer(int fd, char *buf);
char	*grow_line(char *line, size_t line_len, size_t append_len,
			size_t *capacity);
char	*append_line(char *line, size_t *line_len, char *buf,
			size_t append_len);

// get_next_line_utils
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);

#endif