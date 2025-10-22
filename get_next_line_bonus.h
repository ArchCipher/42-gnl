/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:57:31 by kmurugan          #+#    #+#             */
/*   Updated: 2025/10/21 19:54:16 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdint.h> // SIZE_MAX
# include <stdlib.h> // malloc, free
# include <unistd.h> // read, ssize_t

#define MAX_STATIC_BUFFER_SIZE	1073741824 // 1GB

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# if (BUFFER_SIZE * OPEN_MAX) > MAX_STATIC_BUFFER_SIZE
#  undef BUFFER_SIZE
#  define BUFFER_SIZE (MAX_STATIC_BUFFER_SIZE / OPEN_MAX)
# endif

# if BUFFER_SIZE < 1
#  error BUFFER_SIZE too small
# endif

# if BUFFER_SIZE > MAX_STATIC_BUFFER_SIZE
#  error BUFFER_SIZE too large for static allocation
# endif

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