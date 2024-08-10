/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/08/10 15:27:12 by vviterbo         ###   ########.fr       */
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
	if (!(current->current_line))
	{
		write(1, "bla", 3);
		return (NULL);
	}
	write(1, "10_", 3);
	line = ft_strdup(current->current_line);
	write(1, "11_", 3);
	new_block = malloc((1025) * sizeof(char));
	write(1, "12_", 3);
	if (!new_block || !line)
		return (NULL);
	write(1, "13_", 3);
	*(new_block + 1025) = '\0';
	while (ft_strchr(line, '\n') == NULL)
	{
		write(1, "14_", 3);
		read(fd, new_block, 1024);
		if (!new_block)
			return (NULL);
		line = ft_strjoin(line, new_block);
		write(1, "15_", 3);
		if (ft_strlen(new_block) < 1025)
			break ;
	}
	write(1, "16_", 3);
	if (ft_strchr(line, '\n'))
	{
		ft_strlcpy(current->current_line, ft_strchr(line, '\n') + 1,
			ft_strlen(ft_strchr(line, '\n') + 1));
		*(ft_strchr(line, '\n') + 1) = '\0';
	}
	else
		current->current_line = NULL;
	write(1, "17_", 3);
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
	t_open_lines	*first;

	last = NULL;
	if (g_current_lines)
	{
		current = *g_current_lines;
		first = *g_current_lines;
		while (current)
		{
			write(1, "0", 1);
			printf("\ng_current_lines %p\n", *g_current_lines);
			printf("current %p\n", current);
			printf("current->fd vs fd %d, %d\n", current->fd, fd);
			if (current->fd == fd)
			{
				write(1, "><", 2);
				*g_current_lines = first;
				return (current);
			}
			last = current;
			printf("current->next %p\n", current->next);
			current = current->next;
			write(1, "0.1", 3);
		}
	}
	else
	{
		write(1, "1", 1);
		g_current_lines = malloc(sizeof(t_open_lines *));
		first = *g_current_lines;
		if (!g_current_lines)
			return (NULL);
	}
	current = malloc(sizeof(t_open_lines));
	write(1, "2", 1);
	if (!current)
		return (NULL);
	*g_current_lines = current;
	write(1, "3", 1);
	write(1, "4", 1);
	current->current_line = malloc(1025 * sizeof(char));
	if (!current->current_line)
	{
		write(1, "4.1", 3);
		return (NULL);
	}
	write(1, "5", 1);
	*(current->current_line) = '\0';
	current->fd = fd;
	current->next = NULL;
	write(1, "6", 1);
	if (last)
	{
		write(1, "_____", 5);
		printf("last->next %p->%p\n", last, current);
		last->next = current;
	}
	*g_current_lines = first;
	return (current);
}
