#include "get_next_line_bonus.h"

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

char *ft_realloc(char *src, char **l_ptr, ssize_t append_len)
{
    char    *dst;

    if (append_len == 0)
        return (src);
    else if (!src || !l_ptr || !(*l_ptr))
    {
        dst = malloc(append_len + 1);
        if (!dst)
            return (NULL);
        *l_ptr = dst;
        return (dst);
    }
    dst = malloc(l_ptr - src + append_len + 1);
    if (!dst)
        return (src);
    if (src)
    {
        ft_memcpy(dst, src, l_ptr - src);
        l_ptr = dst + (l_ptr - src);
        free(src);
    }
    return (dst);
}
