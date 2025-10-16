#include "get_next_line.h"

void    *ft_memchr(const void *s, int c, ssize_t n)
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

void    *ft_memcpy(void *dst, const void *src, ssize_t n)
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

void    *ft_memmove(void *dst, const void *src, ssize_t len)
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

char *ft_realloc(char *src, ssize_t line_len, ssize_t append_len, ssize_t *capacity)
{
    char    *dst;

    if (append_len <= *capacity - line_len)
        return src;
    else if (*capacity == 0)
        *capacity = append_len;
    else if (*capacity < (SSIZE_MAX / 2) - 1)
        *capacity *= 2;
    else
        *capacity = SSIZE_MAX - 1;
    dst = malloc(*capacity + 1);
    if (!dst)
        return NULL;
    if (src)
    {
        ft_memcpy(dst, src, line_len);
        free(src);
    }
    return (dst);
}
