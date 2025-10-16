#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 255
#endif

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

// get_next_line_bonus
char    *get_next_line(int fd);
size_t	read_file(int fd, char *buf);
size_t	get_append_len(char *buf, char *line, char *l_ptr);
char	*append_line(char *line, char **l_ptr, size_t append_len);

// get_next_line_utils_bonus
void    *ft_memchr(const void *s, int c, ssize_t n);
void    *ft_memcpy(void *dst, const void *src, ssize_t n);
void    *ft_memmove(void *dst, const void *src, ssize_t len);
char *ft_realloc(char *src, char **s_ptr, ssize_t append_len);

#endif
