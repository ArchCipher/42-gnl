/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurugan <kmurugan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:48:41 by kmurugan          #+#    #+#             */
/*   Updated: 2025/10/17 19:23:37 by kmurugan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = src;

	d = dst;
	while (n--)
		*d++ = *s++;
	return (dst);
}

/*
DESCRIPTION
	Locates the first occurrence of the character c in the string s, stops after n bytes or at
	the first null terminator. Returns a pointer to the byte located, or NULL if
	no such character exists within n bytes or if s is NULL.
*/

char    *ft_mstrchr(const char *s, int c, size_t n)
{
	if (!s)
		return (NULL);
    while(n-- > 0 && (unsigned char)*s && ((unsigned char)*s != (unsigned char)c))
        s++;
    if ((unsigned char)*s == (unsigned char)c)
        return ((char *)s);
    return (NULL);
}
