/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/08/10 10:32:23 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_open_lines	**g_current_line = NULL;

char			*get_next_line(int fd);
static char		*init_line(int fd);
static char		*ft_strchr(char *str, char c);

char	*get_next_line(int fd)
{
	char	*line;
	char	*new_block;
	int		n_block;
	size_t	i;

	n_block = 1;
	init_line();
	line = ft_strdup(g_current_line);
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
	ft_strlcpy(g_current_line, ft_strchr(line, '\n') + 1,
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

static char	*init_line(int fd)
{
	t_open_lines	*current;
	t_open_lines	*last;

	last = NULL;
	
	if (g_current_line)
		current = *g_current_line;
	else
	{
		current = malloc(sizeof(t_open_lines));
		if (!current)
			return (NULL);
		g_current_line = &current;
		current->fd = NULL;
	}
	while (current->fd)
	{
		if (current->fd == fd)
			return (current->current_line);
		last = g_current_line;
		g_current_line = current->next;
	}
	g_current_line = malloc(sizeof(t_open_lines));
	if (!g_current_line)
		return (NULL);
	current->current_line = malloc(1025 * sizeof(char));
	if (!current->current_line)
		retunr (NULL);
	*(current->current_line) = '\0';
	current->fd = fd;
	current->next = NULL;
	if (last)
		last->next = current;
	return (g_current_line);
}
