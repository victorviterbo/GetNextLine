/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:29:41 by vviterbo          #+#    #+#             */
/*   Updated: 2024/08/12 21:58:58 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(char *str);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_bzero(void *s, unsigned int n);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*joined;
	unsigned int	i;
	unsigned int	j;

	joined = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1)
			* sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (*(s1 + i))
	{
		*(joined + j) = *(s1 + i);
		i++;
		j++;
	}
	i = 0;
	while (*(s2 + i))
	{
		*(joined + j) = *(s2 + i);
		i++;
		j++;
	}
	return (joined);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*duplicate;

	duplicate = malloc((ft_strlen((char *)s1) + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	ft_strlcpy(duplicate, s1, ft_strlen((char *)s1) + 1);
	return (duplicate);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*(src + i) && i < dstsize - 1)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	while (*(src + i))
		i++;
	return (i);
}

void	ft_bzero(void *s, unsigned int n)
{
	size_t			i;
	unsigned char	*bs;

	i = 0;
	bs = (unsigned char *)s;
	while (i < n)
	{
		*(bs + i) = 0;
		i++;
	}
	return ;
}
