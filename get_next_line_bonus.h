/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:12:40 by crea              #+#    #+#             */
/*   Updated: 2024/08/26 11:41:54 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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