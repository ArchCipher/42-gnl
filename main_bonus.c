#include "get_next_line_bonus.h"

#include <stdio.h>
#include <fcntl.h>

void    print_nl(int fd, unsigned int call)
{
    char *line;
    unsigned int num;

    num = 1;
    while (call--)
    {
        line = get_next_line(fd);
        if (!line)
            return;
        printf("!CALL %d!\n'%s'\n", num, line);
        free(line);
        line = NULL;
        num--;
    }
}

int main()
{
	int fd = open("text.txt", O_RDONLY);
    if (fd < 0)
        return -1;
    unsigned int call = 10;
    print_nl(fd, call);
	close(fd);
}