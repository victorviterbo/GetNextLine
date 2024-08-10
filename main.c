/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:29:04 by vviterbo          #+#    #+#             */
/*   Updated: 2024/08/10 10:08:45 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.c"
#include "get_next_line_utils.c"

int	main(void)
{
	int		fd = open("exemple.txt", O_RDONLY);
	char	*line_str;
	size_t	i = 0;

	while (i < 12)
	{
		line_str = get_next_line(fd);
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", line_str);
		i++;
	}
}