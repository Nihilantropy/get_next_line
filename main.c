/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:02:45 by crea              #+#    #+#             */
/*   Updated: 2024/08/26 12:03:20 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define FILE_NAME "sample.txt"

int	main(void)
{
	int		fd;
	char	*line;

	// Open the file for reading
	fd = open(FILE_NAME, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}

	// Read lines from the file and print them
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);  // Print the line
		free(line);           // Free the allocated memory for the line
	}

	// Close the file descriptor
	close(fd);

	return (0);
}