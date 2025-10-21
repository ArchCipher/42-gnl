/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:31:14 by kmurugan          #+#    #+#             */
/*   Updated: 2025/10/21 19:16:10 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_bonus.h"
#include <fcntl.h> // open
#include <stdio.h> // printf
#include <time.h>

void	print_nl(int fd)
{
	char			*line;
	unsigned int	num;

	num = 1;
	line = get_next_line(fd);
	printf("[%d]: %s", num++, line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
		{
			printf("[%d]:%s", num++, line);
			return ;
		}
		printf("[%d]:%s", num++, line);
	}
	free(line);
	return ;
}

char *my_malloc(size_t size)
{
	int r = rand() % 100;
	if (r < 10)
		return (NULL);
	return (malloc(size));
}

int	main(void)
{
	srand(time(NULL));
	int fd = open("text.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	print_nl(fd);
	close(fd);

	// int i = 0;
	// while (i <= 1048576)
	// {
	// 	fd = open("text.txt", O_RDONLY);
	// 	if (!fd)
	// 		printf("%d\n", i);
	// 	i++;
	// }
	// close(fd);
}