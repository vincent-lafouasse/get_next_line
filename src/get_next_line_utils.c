/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:53:56 by poss              #+#    #+#             */
/*   Updated: 2024/04/05 18:46:55 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <stdlib.h>

typedef unsigned char t_byte;

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	t_byte	*dest_bytes;
	t_byte	*src_bytes;

	dest_bytes = (t_byte *)dest;
	src_bytes = (t_byte *)src;
	while (n)
	{
		*dest_bytes = *src_bytes;
		n--;
		dest_bytes++;
		src_bytes++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*out;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = malloc(len1 + len2 + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, s1, len1);
	ft_memcpy(out + len1, s2, len2);
	out[len1 + len2] = '\0';
	return (out);
}

char	*ft_strdup(const char *s)
{
	char	*out;
	size_t	len;

	len = ft_strlen(s);
	out = malloc(1 + len);
	if (!out)
		return (NULL);
	ft_memcpy(out, s, 1 + len);
	return (out);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == (unsigned char)c)
		{
			return ((char *)s);
		}
		if (*s == '\0')
		{
			return (NULL);
		}
		s++;
	}
}
