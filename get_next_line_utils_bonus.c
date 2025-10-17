#include "get_next_line_bonus.h"

void    *ft_memchr(const void *s, int c, size_t n)
{
    const unsigned char *str;

    str = (const unsigned char *)s;
    while(n-- > 0)
    {
        if (*str == (unsigned char)c)
            return ((void *)str);
        str++;
    }
    return NULL;
}

void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d;
    const unsigned char *s;

    if (!dst && !src && n > 0)
        return (NULL);
    d = (unsigned char *)dst;
    s = (unsigned char *)src;
    while(n-- > 0)
    {
        *(d++) = *(s++);
    }
    return (dst);
}

void    *ft_memmove(void *dst, const void *src, size_t len)
{
    unsigned char *d;
    const unsigned char *s;

    if (dst == src || len == 0)
        return dst;
    d = (unsigned char *)dst;
    s = (unsigned char *)src;
    if (d < s)
    {
        while(len-- > 0)
            *(d++) = *(s++);
    }
    else
    {
        d += len;
        s += len;
        while(len-- > 0)
            *(--d) = *(--s);
    }
    return dst;
}

char *ft_realloc(char *line, size_t line_len, size_t capacity)
{
    char    *dst;

    dst = malloc(capacity);
    if (!dst)
        return NULL;
    if (line)
    {
        ft_memcpy(dst, line, line_len);
        free(line);
    }
    return (dst);
}
