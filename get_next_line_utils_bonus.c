#include "get_next_line_bonus.h"

size_t  ft_strlen(const char *s)
{
    size_t  n;

    n = 0;
    while(s[n])
        n++;
    return (n);
}

ssize_t  find_nl(const char *s, ssize_t n)
{
    ssize_t  i;

    i = 0;
    while(i < n)
    {
        if (s[i] == '\n')
            return (i + 1);
        i++;
    }
    return (n);
}

void *ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d = dst;
    const unsigned char *s = src;
    while (n--)
        *d++ = *s++;
    return dst;
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
