#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// #ifndef BUFFER_SIZE
// #define BUFFER_SIZE 64
// #endif

#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

char *get_next_line(int fd);
void    *ft_memchr(const void *s, int c, size_t n);
void    *ft_memcpy(void *dst, const void *src, size_t n);
void    *ft_memmove(void *dst, const void *src, size_t len);
char *ft_realloc(char *src, size_t old_len, size_t new_len);

#endif
