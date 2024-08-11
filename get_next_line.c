/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/08/11 11:15:19 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_open_lines	*g_current_lines = NULL;

char				*get_next_line(int fd);
static t_open_lines	*init_line(int fd);
static char			*ft_strchr(char *str, char c);

char	*get_next_line(int fd)
{
	char			*line;
	char			*new_block;
	t_open_lines	*current;

	current = init_line(fd);
	if (!(current) || !(current->current_line))
		return (NULL);
	line = ft_strdup(current->current_line);
	new_block = malloc((1025) * sizeof(char));
	if (!new_block || !line)
		return (NULL);
	*(new_block + 1025) = '\0';
	while (ft_strchr(line, '\n') == NULL)
	{
		read(fd, new_block, 1024);
		line = ft_strjoin(line, new_block);
		if (ft_strlen(new_block) < 1025)
			break ;
	}
	if (ft_strchr(line, '\n'))
	{
		ft_strlcpy(current->current_line, ft_strchr(line, '\n') + 1,
			ft_strlen(ft_strchr(line, '\n') + 1));
		*(ft_strchr(line, '\n') + 1) = '\0';
	}
	else
		current->current_line = NULL;
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

	if (g_current_lines)
	{
		current = g_current_lines;
		while (current->next)
		{
			//printf("current in loop = %p\n", current);
			if (current->fd == fd)
				return (current);
			current = current->next;
			//printf("next in loop = %p\n", current);
		}
		if (current->fd == fd)
			return (current);
		current->next = malloc(sizeof(t_open_lines));
		current = current->next;
		//printf("adding to the stack %p\n", current);
	}
	else
	{
		g_current_lines = malloc(sizeof(t_open_lines));
		if (!g_current_lines)
			return (NULL);
		current = g_current_lines;
		//printf("adding to the stack %p\n", current);
	}
	current->current_line = malloc(1025 * sizeof(char));
	if (!current->current_line)
		return (NULL);
	*(current->current_line) = '\0';
	current->fd = fd;
	current->next = NULL;
	return (current);
}
