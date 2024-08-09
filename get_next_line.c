/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/08/08 12:47:38 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*get_next_line(int fd);
static char		*init_line(void);

static char	*g_current_line = NULL;

char	*get_next_line(int fd)
{
	char	*line;
	char	*new_block;
	int		n_block;
	size_t	i;

	n_block = 1;
	line = init_line();
	new_block = malloc((1025) * sizeof(char));
	if (!new_block)
		return (NULL);
	*(new_block + 1025) = '\0';
	while (i == 1024)
	{
		i = 0;
		read(fd, new_block, 1024);
		while (*(new_block + i) && *(new_block + i) != '\n')
			i++;
		if (i < 1025)
			break ;
		line = ft_strjoin(line, new_block);
	}
	g_current_line = ft_strcpy(new_block + i + 1);
	*(new_block + i + 1) = '\0';
	line = ft_strjoin(line, new_block);
	free(new_block);
	return (line);
}

static char	*init_line(void)
{
	if (g_current_line)
		return (g_current_line);
	g_current_line = malloc(1025 * sizeof(char));
	if (!g_current_line)
		return (NULL);
	*g_current_line = '\0';
	return (g_current_line);
}
