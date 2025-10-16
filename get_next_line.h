#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 64
#endif

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

// get_next_line
char    *get_next_line(int fd);
char	*append_line(char *line, char *buf, const char *nlp, ssize_t bytes_read);
ssize_t	get_append_len(char *buf, const char *nlp, ssize_t line_len, ssize_t bytes_read);

// get_next_line_utils
void    *ft_memchr(const void *s, int c, ssize_t n);
void    *ft_memcpy(void *dst, const void *src, ssize_t n);
void    *ft_memmove(void *dst, const void *src, ssize_t len);
char    *ft_realloc(char *src, ssize_t line_len, ssize_t append_len, ssize_t *capacity);

#endif
