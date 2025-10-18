/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:57:31 by kmurugan          #+#    #+#             */
/*   Updated: 2025/10/17 19:06:07 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdint.h> // SIZE_MAX
# include <stdlib.h> // malloc, free
# include <unistd.h> // read, ssize_t

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// get_next_line
char	*get_next_line(int fd);
ssize_t	get_append_len(int fd, char *buf);
size_t	calculate_new_capacity(size_t line_len, size_t append_len, char *buf);
char	*append_line(char *line, size_t *line_len, char *buf,
			size_t append_len);

// get_next_line_utils
size_t	ft_strlen(const char *s);
ssize_t	find_nl(const char *s, ssize_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_realloc(char *line, size_t line_len, size_t capacity);

#endif