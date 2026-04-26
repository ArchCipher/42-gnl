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
#include <time.h>  // rand

// Uncomment to test malloc failure scenarios (for leak checking)
// char *my_malloc(size_t size)
// {
// 	int r = rand() % 100;
// 	if (r < 10)
// 		return (NULL);
// 	return (malloc(size));
// }

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
