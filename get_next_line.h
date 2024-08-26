/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:59:36 by crea              #+#    #+#             */
/*   Updated: 2024/08/26 11:31:38 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

/* define BUFFER SIZE if not defined */
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

/* list data structure */
typedef struct	s_list
{
	char			*data;
	struct  s_list	*next;
}	t_list;
/* get next line */
char	*get_next_line(int fd);

#endif
