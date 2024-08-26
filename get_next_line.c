/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 02:35:30 by crea              #+#    #+#             */
/*   Updated: 2024/08/26 11:22:50 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	create_buffer(t_list **list, int fd);
static void	create_new_node(t_list **list, char *buffer);
static char	*extract_line(t_list *list);
static void	polish_list(t_list **list);
void		clean_list(t_list **list, t_list *new_head, char *buffer);
void		cpy_nodes(char *line, t_list *list);
int			len_to_newline(t_list *list);
int 		find_newline(t_list *list);
t_list  	*find_last_node(t_list *list);

/*	get_next_line:
		Reads a line from the given file descriptor 'fd'.
		The function manages multiple file descriptors using a static linked list. 
		It checks the validity of the file descriptor and BUFFER_SIZE, 
		then creates or retrieves the buffer for the file descriptor, extracts a line from it, 
		and polishes the list by removing the processed data.
		Returns the line read from the file descriptor, or NULL if an error
		occurs or if the end of the file is reached.
*/
char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	create_buffer(&list, fd);
	if (!list)
		return (NULL);
	line = extract_line(list);
	polish_list(&list);
	return (line);  
}

/*	create_buffer:
		Reads data from the file descriptor 'fd' and appends it to
		the linked list 'list' until a newline is found.
		The function continuously allocates a buffer, reads up to 'BUFFER_SIZE'
		bytes into it, and 
		then creates a new node in the list with the read data. If a newline character
		is detected in the list, the reading stops. In case of a memory allocation
		failure or if the read function returns 0 (indicating end of file), the function
		stops and cleans up.
*/
static void	create_buffer(t_list **list, int fd)
{
	ssize_t	bytes_read;
	char	*buffer;

	while (!(find_newline(*list)))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		create_new_node(list, buffer);
	}
}

/*	create_new_node:
		Creates a new node containing the 'buffer' and appends it to the
		end of the linked list 'list'.
		The function allocates memory for a new 't_list' node and assigns
		the 'buffer' to the node's data field.
		If the list is empty, the new node becomes the first node in the list.
		Otherwise, it is appended to the end of the list.
		The function ensures the 'next' pointer of the new node is set to NULL.
*/
static void	create_new_node(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->data = buffer;
	new_node->next = NULL;
}

/*	extract_line:
		Extracts a line from the linked list 'list' by copying characters
		up to and including the first newline.
		The function calculates the length of the line to be extracted using
		'len_to_newline' and then allocates memory for the line.
		It copies the content of the nodes into the allocated string 'line'.
		Returns the extracted line or NULL if memory allocation fails.
*/
static char	*extract_line(t_list *list)
{
	char	*line;
	int		len;

	len = len_to_newline(list);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	cpy_nodes(line, list);
	return (line);
}

/*	polish_list:
		Adjusts the linked list 'list' by removing the part of the last node's
		data that has already been processed.
		The function creates a new node 'new_head' and a buffer to store the
		remaining data after the newline.
		It finds the last node in the list and copies the unprocessed data (after the newline)
		into the buffer.
		This new buffer is then assigned to 'new_head', which is added as the new head of the list.
		Finally, the function calls 'clean_list' to update and clean up the list structure.
*/
static void	polish_list(t_list **list)
{
	t_list	*new_head;
	t_list	*last_node;
	char	*buffer;
	int		i;
	int		j;

	buffer = malloc(BUFFER_SIZE + 1);
	new_head = malloc(sizeof(t_list));
	if (!buffer || !new_head)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	j = 0;
	while (last_node->data[i] && last_node->data[i] != '\n')
		i++;
	while (last_node->data[i] && last_node->data[i++])
		buffer[j++] = last_node->data[i];
	buffer[j] = '\0';
	new_head->data = buffer;
	new_head->next = NULL;
	clean_list(list, new_head, buffer);
}
