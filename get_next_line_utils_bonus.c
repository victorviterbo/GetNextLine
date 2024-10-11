/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:29:41 by vviterbo          #+#    #+#             */
/*   Updated: 2024/10/11 21:40:33 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2, int free_s1);
size_t	ft_strlen(char *str);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_calloc(size_t count, size_t size);

char	*ft_strjoin(char const *s1, char const *s2, int in_place)
{
	char			*joined;

	joined = ft_calloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1,
			sizeof(char));
	if (!joined)
	{
		if (in_place == 1)
			free((void *)s1);
		else if (in_place == 2)
			free((void *)s2);
		return (NULL);
	}
	ft_strlcpy(joined, s1, ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	ft_strlcpy(joined + ft_strlen((char *)s1), s2, ft_strlen((char *)s2) + 1);
	if (in_place == 1)
		free((void *)s1);
	else if (in_place == 2)
		free((void *)s2);
	return (joined);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*(str + i))
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*duplicate;

	duplicate = ft_calloc((ft_strlen((char *)s1) + 1), sizeof(char));
	if (!duplicate)
		return (NULL);
	ft_strlcpy(duplicate, s1, ft_strlen((char *)s1) + 1);
	return (duplicate);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*(src + i) && i + 1 < dstsize)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	if (dstsize)
		*(dst + i) = '\0';
	while (*(src + i))
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*bptr;
	size_t			i;

	i = 0;
	if (!count || !size)
		return (malloc(1));
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
