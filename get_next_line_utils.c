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

char *ft_realloc(char *src, size_t old_len, size_t new_len)
{
    char *dst;

    if (new_len == 0)
        return NULL;
    if (old_len >= new_len)
        return src;
    dst = malloc(new_len);
    if (!dst)
        return NULL;
    if (src)
    {
        dst = ft_memcpy(dst, src, old_len);
        free(src);
    }
    return (dst);
}


int main()
{
    char *line1;
    char *line2;

	int fd = open("text.txt", O_RDONLY);
	printf("!CALL 1!\n");
    line1 = get_next_line(fd);
	printf("'%s'\n",line1);
    free(line1);
    printf("!CALL 2!\n");
    line2 = get_next_line(fd);
	printf("'%s'\n",line1);
    free(line2);
	printf("!CALL 3!\n");
	printf("'%s'\n",get_next_line(fd));
	printf("!CALL 4!\n");
	printf("'%s'\n",get_next_line(fd));
	close(fd);
}
