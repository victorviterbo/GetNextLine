/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/08/12 22:01:57 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_open_lines	*g_lst_files = NULL;

char				*get_next_line(int fd);
static t_open_lines	*new_file(int fd);
static char			*ft_strchr(char *str, char c);
void				*ft_calloc(size_t count, size_t size);
void				free_open_line(t_open_lines *todel);

char	*get_next_line(int fd)
{
	char			*line;
	char			*new_block;
	t_open_lines	*current;
	size_t			bytes_read;

	bytes_read = 1;
	current = new_file(fd);
	printf("1\n");
	if (!(current) || !(current->current_line))
		return (NULL);
	line = ft_strdup(current->current_line);
	printf("2\n");
	new_block = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!new_block || !line)
		return (NULL);
	printf("3\n");
	while (ft_strchr(line, '\n') == NULL && bytes_read)
	{
		bytes_read = read(fd, new_block, BUFFER_SIZE);
		*(new_block + bytes_read) = '\0';
		line = ft_strjoin(line, new_block);
		if (!line || ! *line)
			return (NULL);
	}
	if (bytes_read)
	{
		printf("4\n");
		ft_strlcpy(current->current_line, ft_strchr(line, '\n') + 1,
			ft_strlen(ft_strchr(line, '\n')));
		*(ft_strchr(line, '\n') + 1) = '\0';
	}
	else
	{

		printf("5\n");
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

static t_open_lines	*new_file(int fd)
{
	t_open_lines	*current;

	if (g_lst_files)
	{
		current = g_lst_files;
		while (current->next && current->fd != fd)
			current = current->next;
		if (current->fd == fd)
			return (current);
		current->next = malloc(sizeof(t_open_lines));
		current = current->next;
	}
	else
	{
		g_lst_files = malloc(sizeof(t_open_lines));
		current = g_lst_files;
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

void	free_open_line(t_open_lines *todel)
{
	t_open_lines	*current;

	current = g_lst_files;
	if (current == todel)
	{
		g_lst_files = current->next;
		free(current->current_line);
		free(current);
		return ;
	}
	while (current->next && current->next != todel)
		current = current->next;
	if (current->next != todel)
		return ;
	current->next = current->next->next;
	free(current->next->current_line);
	free(current->next);
	return ;
}
