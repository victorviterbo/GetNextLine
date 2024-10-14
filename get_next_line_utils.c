/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:29:41 by vviterbo          #+#    #+#             */
/*   Updated: 2024/10/14 14:55:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2, int free_s1);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);

char	*ft_strjoin(char const *s1, char const *s2, int in_place)
{
	char	*joined;
	size_t	s2len;

	if (ft_strchr(s2, '\n'))
		s2len = (size_t)(ft_strchr(s2, '\n') - s2) + 1;
	else
		s2len = ft_strlen(s2);
	joined = ft_calloc(ft_strlen(s1) + s2len + 1, sizeof(char));
	if (!joined)
	{
		if (in_place == 1)
			free((void *)s1);
		else if (in_place == 2)
			free((void *)s2);
		return (NULL);
	}
	ft_memmove(joined, s1, ft_strlen(s1));
	ft_memmove(joined + ft_strlen(s1), s2, s2len);
	*(joined + ft_strlen(s1) + s2len) = '\0';
	if (in_place == 1)
		free((void *)s1);
	else if (in_place == 2)
		free((void *)s2);
	return (joined);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*(str + i))
		i++;
	return (i);
}

char	*ft_strndup(const char *s1, size_t size)
{
	char	*duplicate;

	duplicate = ft_calloc(size, sizeof(char));
	if (!duplicate)
		return (NULL);
	ft_memmove(duplicate, s1, size);
	return (duplicate);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int						i;

	if (!dst || ! src)
		return (NULL);
	if (src < dst && dst < src + n)
	{
		i = n - 1;
		while (i + 1)
		{
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while ((size_t)i < n)
		{
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
			i++;
		}	
	}
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*bptr;
	size_t			i;

	i = 0;
	if (!count || !size)
		return (malloc(0));
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	bptr = (unsigned char *)ptr;
	while (i < (count * size))
	{
		*(bptr + i) = '\0';
		i++;
	}
	return (ptr);
}
