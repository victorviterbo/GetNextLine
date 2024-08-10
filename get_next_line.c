/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/08/10 12:05:52 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_open_lines	**g_current_lines = NULL;

char				*get_next_line(int fd);
static t_open_lines	*init_line(int fd);
static char			*ft_strchr(char *str, char c);

char	*get_next_line(int fd)
{
	char			*line;
	char			*new_block;
	int				n_block;
	t_open_lines	*current;

	n_block = 1;
	current = init_line(fd);
	line = ft_strdup(current->current_line);
	new_block = malloc((1025) * sizeof(char));
	if (!new_block || !line)
		return (NULL);
	*(new_block + 1025) = '\0';
	while (ft_strchr(line, '\n') == NULL)
	{
		read(fd, new_block, 1024);
		if (!new_block)
			return (NULL);
		line = ft_strjoin(line, new_block);
		if (ft_strlen(new_block) < 1025)
			break ;
	}
	ft_strlcpy(current->current_line, ft_strchr(line, '\n') + 1,
		ft_strlen(ft_strchr(line, '\n') + 1));
	*(ft_strchr(line, '\n') + 1) = '\0';
	free(new_block);
	return (line);
}

static char	*ft_strchr(char *str, char c)
{
	size_t	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == c)
			return (str + i);
		i++;
	}
	return (NULL);
}

static t_open_lines	*init_line(int fd)
{
	t_open_lines	*current;
	t_open_lines	*last;

	last = NULL;
	if (g_current_lines)
	{
		current = *g_current_lines;
		while (current)
		{
			if (current->fd == fd)
				return (current);
			last = current;
			current = current->next;
		}
	}
	else
	{
		g_current_lines = malloc(sizeof(t_open_lines *));
		if (!g_current_lines)
			return (NULL);
		current = malloc(sizeof(t_open_lines));
		if (!current)
			return (NULL);
		*g_current_lines = current;
		current->fd = -2;
	}
	current->current_line = malloc(1025 * sizeof(char));
	if (!current->current_line)
		return (NULL);
	*(current->current_line) = '\0';
	current->fd = fd;
	current->next = NULL;
	if (last)
		last->next = current;
	return (current);
}
