/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2024/10/11 13:45:49 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char				*get_next_line(int fd);
static char			*agglutinate(int fd, t_open_lines **g_lst_files,
						t_open_lines *current, char *line);
static t_open_lines	*new_file(int fd, t_open_lines **g_lst_files);
static void			free_open_line(t_open_lines *todel,
						t_open_lines **g_lst_files);
char				*ft_strchr(const char *s, int c);

char	*get_next_line(int fd)
{
	char				*line;
	t_open_lines		*current;
	static t_open_lines	**g_lst_files = NULL;

	if (!g_lst_files)
		g_lst_files = ft_calloc(1, sizeof(t_open_lines *));
	if (!g_lst_files)
		return (NULL);
	current = new_file(fd, g_lst_files);
	if (!(current) || !(current->current_line))
		return (NULL);
	line = ft_strdup(current->current_line);
	line = agglutinate(fd, g_lst_files, current, line);
	return (line);
}

static char	*agglutinate(int fd, t_open_lines **g_lst_files,
	t_open_lines *current, char *line)
{
	size_t	bytes_read;
	char	*new_block;

	bytes_read = 1;
	new_block = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!new_block || !line)
		return (NULL);
	while (ft_strchr(line, '\n') == NULL && bytes_read)
	{
		bytes_read = read(fd, new_block, BUFFER_SIZE);
		*(new_block + bytes_read) = '\0';
		line = ft_strjoin(line, new_block);
		if (!line || !*line)
			return (NULL);
	}
	if (bytes_read)
	{
		ft_strlcpy(current->current_line, ft_strchr(line, '\n') + 1,
			ft_strlen(ft_strchr(line, '\n')));
		*(ft_strchr(line, '\n') + 1) = '\0';
	}
	else
		free_open_line(current, g_lst_files);
	free(new_block);
	return (line);
}

static t_open_lines	*new_file(int fd, t_open_lines **g_lst_files)
{
	t_open_lines	*current;

	if (*g_lst_files)
	{
		current = *g_lst_files;
		while (current->next && current->fd != fd)
			current = current->next;
		if (current->fd == fd)
			return (current);
		current->next = malloc(sizeof(t_open_lines));
		current = current->next;
	}
	else
	{
		current = malloc(sizeof(t_open_lines));
		*g_lst_files = current;
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

static void	free_open_line(t_open_lines *todel, t_open_lines **g_lst_files)
{
	t_open_lines	*current;

	current = *g_lst_files;
	if (current == todel)
	{
		*g_lst_files = current->next;
		free(current->current_line);
		free(current);
		if (!*g_lst_files)
		{
			free(g_lst_files);
			g_lst_files = NULL;
		}
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

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	i = 0;
	uc = (unsigned char)c;
	while (*(s + i))
	{
		if ((unsigned char)*(s + i) == uc)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	else
		return (NULL);
}
