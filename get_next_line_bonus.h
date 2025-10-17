#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

// get_next_line
char    *get_next_line(int fd);
size_t	get_valid_bytes(int fd, char *buf);
size_t	get_append_len(char *buf, size_t line_len, ssize_t valid_bytes);
char	*append_line(char *line, size_t line_len, char *buf, size_t append_len);

// get_next_line_utils
void    *ft_memchr(const void *s, int c, size_t n);
void    *ft_memcpy(void *dst, const void *src, size_t n);
void    *ft_memmove(void *dst, const void *src, size_t len);
char *ft_realloc(char *line, size_t line_len, size_t capacity);

#endif