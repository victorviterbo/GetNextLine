/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/08/12 18:00:55 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_open_lines	*g_open_lines = NULL;

char				*get_next_line(int fd);
static t_open_lines	*init_line(int fd);
static char			*ft_strchr(char *str, char c);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, unsigned int n);
void				free_open_line(t_open_lines *todel);

char	*get_next_line(int fd)
{
	char			*line;
	char			*new_block;
	t_open_lines	*current;
	size_t			bytes_read;

	bytes_read = 1;
	current = init_line(fd);
	if (!(current) || !(current->current_line))
		return (NULL);
	line = ft_strdup(current->current_line);
	new_block = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!new_block || !line)
		return (NULL);
	while (ft_strchr(line, '\n') == NULL && bytes_read)
	{
		bytes_read = read(fd, new_block, BUFFER_SIZE);
		*(new_block + bytes_read) = '\0';
		line = ft_strjoin(line, new_block);
		if (!line)
			return (NULL);
	}
	if (bytes_read)
	{
		ft_strlcpy(current->current_line, ft_strchr(line, '\n') + 1,
			ft_strlen(ft_strchr(line, '\n')));
		*(ft_strchr(line, '\n') + 1) = '\0';
	}
	else
	{
		free_open_line(current);
	}
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

	if (g_open_lines)
	{
		current = g_open_lines;
		while (current->next && current->fd != fd)
			current = current->next;
		if (current->fd == fd)
			return (current);
		current->next = malloc(sizeof(t_open_lines));
		current = current->next;
	}
	else
	{
		g_open_lines = malloc(sizeof(t_open_lines));
		current = g_open_lines;
	}
	if (!current)
		return (NULL);
	current->current_line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!current->current_line)
		return (NULL);
	current->fd = fd;
	current->next = NULL;
	return (current);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count);
	return (ptr);
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

void	free_open_line(t_open_lines *todel)
{
	t_open_lines	*current;

	current = g_open_lines;
	if (current == todel)
	{
		g_open_lines = current->next;
		free(current->current_line);
		free(current);
	}
	while (current->next && current->next != todel)
	{
		current = current->next;
	}
	if (current->next != todel)
		return ;
	current->next = current->next->next;
	free(current->next->current_line);
	free(current->next);
	return ;
}
