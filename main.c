/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:29:04 by vviterbo          #+#    #+#             */
/*   Updated: 2024/10/10 15:54:43 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd1 = open("exemple1.txt", O_RDONLY);
	char	*line_1;
	size_t	i = 0;

	printf("BUFFER SIZE = %i\n", BUFFER_SIZE);
	while (i < 24)
	{
		line_1 = get_next_line(fd1);
		if (line_1)
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", line_1);
		i++;
	}
}