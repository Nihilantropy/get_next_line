/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:12:07 by crea              #+#    #+#             */
/*   Updated: 2024/08/26 11:44:21 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	create_buffer(t_list **list, int fd);
static void	create_new_node(t_list **list, char *buffer, int fd);
static char	*extract_line(t_list *list);
static void	polish_list(t_list **list);
void		clean_list(t_list **list, t_list *new_head, char *buffer);
void		cpy_nodes(char *line, t_list *list);
int			len_to_newline(t_list *list);
int 		find_newline(t_list *list);
t_list  	*find_last_node(t_list *list);

/*	get_next_line:
		Reads a line from the file descriptor 'fd' and returns it as a
		dynamically allocated string.
		The function handles multiple file descriptors by using a static
		array of linked lists to store data.
		It performs the following steps:
		1. Validates the file descriptor and buffer size. If invalid, it returns NULL.
		2. Calls 'create_buffer' to populate the linked list with data read from the file
			descriptor.
		3. If no data was read (i.e., the list is empty), it returns NULL.
		4. Extracts a line from the linked list using 'extract_line'.
		5. Cleans up the linked list by calling 'polish_list', which adjusts the list for
			remaining data.
		6. Returns the extracted line.
		This function is designed to handle large files efficiently and to support
		multiple simultaneous file descriptors.
*/
char	*get_next_line(int fd)
{
	static	t_list *list[4096];
	char	*line;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	create_buffer(list, fd);
	if (!list[fd])
		return (NULL);
	line = extract_line(list[fd]);
	polish_list(&list[fd]);
	return(line);
}

/*	create_buffer:
		Fills the linked list 'list' associated with the file descriptor 'fd'
		with data from the file.
		The function repeatedly reads from the file descriptor until a newline
		character is found in the list.
		For each read operation, it allocates a buffer, reads data into it, and adds
		it to the linked list.
		If the read operation returns 0 (end of file) or an error occurs, it frees
		the allocated buffer and returns.
		The function ensures that the linked list has the complete data needed to
		extract a full line.
*/
static void	create_buffer(t_list **list, int fd)
{
	ssize_t	bytes_read;
	char	*buffer;

	while (!(find_newline(list[fd])))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
		{
			free (buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		create_new_node(list, buffer, fd);
	}
}

/*	create_new_node:
		Creates a new node in the linked list 'list' for the file descriptor 'fd'.
		The function allocates memory for a new list node and assigns the provided 'buffer' to it.
		It then finds the last node in the linked list and appends the new node to it.
		If the list is empty, the new node becomes the head of the list.
		If the allocation fails, the function does nothing and returns.
*/
static void	create_new_node(t_list **list, char *buffer, int fd)
{
	t_list	*new_node;
	t_list	*last_node;

    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return ;
    new_node->data = buffer;
    new_node->next = NULL;
    last_node = find_last_node(list[fd]);
    if (!last_node)
        list[fd] = new_node;
    else
        last_node->next = new_node;
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
	int		i;
	int		j;
	char	*buffer;
	t_list	*last_node;
	t_list	*new_head;

	new_head = malloc(sizeof(t_list));
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer || !new_head)
		return ;
	i = 0;
	j = 0;
	last_node = find_last_node(*list);
	while (last_node->data[i] && last_node->data[i] != '\n')
		i++;
	while (last_node->data[i] && last_node->data[i++])
		buffer[j++] = last_node->data[i];
	buffer[j] = '\0';
	new_head->data = buffer;
	new_head->next = NULL;
	clean_list(list, new_head, buffer);
}
