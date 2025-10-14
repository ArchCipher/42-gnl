#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 64
#endif

#include <stdlib.h>
#include <unistd.h>

// get_next_line_bonus
char    *get_next_line(int fd);
char	*append_line(char *line, size_t *line_len, char *buf, char **buf_pos);
char	*get_append_len(size_t line_len, char *buf, char *buf_pos, size_t *append_len);

// get_next_line_utils_bonus
void    *ft_memchr(const void *s, int c, size_t n);
void    *ft_memcpy(void *dst, const void *src, size_t n);
void    *ft_memmove(void *dst, const void *src, size_t len);
char    *ft_realloc(char *src, size_t line_len, size_t append_len);

#endif
