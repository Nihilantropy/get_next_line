/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 02:35:27 by crea              #+#    #+#             */
/*   Updated: 2024/08/26 11:28:46 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*	clean_list:
		Cleans up the linked list 'list' by freeing all its nodes and their associated data.
		The function iterates through each node, frees its data, and then frees the node itself.
		Once the list is cleared, it checks if the 'new_head' contains any data.
		If 'new_head' has data, it becomes the new head of the list; otherwise,
		'new_head' and the buffer are freed.
		This function ensures that the list is either reset with the new head or completely cleared.
*/
void	clean_list(t_list **list, t_list *new_head, char *buffer)
{
	t_list	*temp;

	if (!*list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->data);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (new_head->data[0])
		(*list) = new_head;
	else
	{
		free(buffer);
		free(new_head);
	}
}

/*	cpy_nodes:
		Copies the contents of each node's data in the linked list 'list'
		into the string 'line'.
		The function iterates through the list, copying characters one by one
		from each node's data into 'line'.
		If a newline character ('\n') is encountered, it is also copied, and the
		function terminates the string with '\0'.
		If no newline is found, the function continues until all characters are copied,
		and then null-terminates the string.
		This function effectively assembles the complete line from the list's nodes.
*/
void	cpy_nodes(char *line, t_list *list)
{
	int	i;
	int	j;

	j = 0;
	while (list)
	{
		i = 0;
		while (list->data[i])
		{
			if (list->data[i] == '\n')
			{
				line[j++] = list->data[i];
				line[j] = '\0';
				return ;
			}
			line[j++] = list->data[i++];
		}
		list = list->next;
	}
	line[j] = '\0';
	return ;
}

/*	len_to_newline:
		Calculates the length of the data in the linked list 'list' up to and
		including the first newline character ('\n').
		The function traverses each node in the list and counts characters until
		a newline is found.
		If a newline is encountered, it increments the length by one and returns
		the total length including the newline.
		If no newline is found, it returns the length of all characters in the list.
		This function helps in determining the length of the string to be extracted
		up to the first newline.
*/
int	len_to_newline(t_list *list)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->data[i])
		{
			if (list->data[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

/*	find_newline:
		Checks if there is a newline character ('\n') in the linked list 'list'.
		The function iterates through each node in the list and examines the data in each node.
		It scans up to BUFFER_SIZE characters per node to find a newline.
		If a newline character is found, the function returns 1.
		If no newline is found after checking all nodes, the function returns 0.
		This function helps in determining whether the list contains a complete
		line ending with a newline character.
*/
int find_newline(t_list *list)
{
	int	i;

	if(!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->data[i] && i < BUFFER_SIZE)
		{
			if (list->data[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

/*	find_last_node:
		Finds and returns the last node in the linked list 'list'.
		The function traverses the list from the head, moving to the next node until
		it reaches the last node.
		The last node is identified by checking that its 'next' pointer is NULL.
		If the list is empty (NULL), the function returns NULL.
		This function is useful for appending new nodes to the end of the
		list or for operations that require access to the last element.
*/
t_list  *find_last_node(t_list *list)
{
	if (!list)
		return (NULL); 
	while (list->next)
		list = list->next;
	return(list);
}
