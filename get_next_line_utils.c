#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>


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

char *ft_realloc(char *src, size_t line_len, size_t new_len)
{
    char *dst;

    if (new_len < 1)
        return NULL;
    if (line_len >= new_len)
        return src;
    dst = malloc(new_len);
    if (!dst)
        return NULL;
    if (src)
    {
        dst = ft_memcpy(dst, src, line_len);
        free(src);
    }
    return (dst);
}

void    print_nl(int fd)
{
    char *line;

    line = get_next_line(fd);
    printf("'%s'\n",line);
    free(line);
    line = NULL;
}

int main()
{
	int fd = open("text.txt", O_RDONLY);
    if (fd < 0)
        return -1;
	printf("!CALL 1!\n");
    print_nl(fd);
    printf("!CALL 2!\n");
    print_nl(fd);
	printf("!CALL 3!\n");
    print_nl(fd);
	printf("!CALL 4!\n");
	print_nl(fd);
	close(fd);
}
