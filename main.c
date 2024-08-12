/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:29:04 by vviterbo          #+#    #+#             */
/*   Updated: 2024/08/12 23:35:20 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.c"
#include "get_next_line_utils.c"

int	main(void)
{
	int		fd1 = open("exemple1.txt", O_RDONLY);
	int		fd2 = open("exemple2.txt", O_RDONLY);
	int		fd3 = open("exemple3.txt", O_RDONLY);
	char	*line_1;
	char	*line_2;
	char	*line_3;
	size_t	i = 0;

	printf("BUFFER SIZE = %i\n", BUFFER_SIZE);
	while (i < 24)
	{
		line_1 = get_next_line(fd1);
		if (line_1)
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", line_1);
		line_2 = get_next_line(fd2);
		if (line_2)
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", line_2);
		line_3 = get_next_line(fd3);
		if (line_3)
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", line_3);
		printf("------------------------------------------------------------------------------\n");
		i++;
	}
}