/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:55:39 by nzharkev          #+#    #+#             */
/*   Updated: 2024/06/07 10:57:08 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	create_list(t_gnl_list **list, int fd)
{
	int		c;
	char	*buffer;

	c = 1;
	while (!find_nl(*list) && c != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
		{
			list_emptier(list, NULL);
			return ;
		}
		c = read(fd, buffer, BUFFER_SIZE);
		if (c == -1 || c == 0)
		{
			free(buffer);
			buffer = NULL;
			if (!(*list) && c == 0)
				list_emptier(list, NULL);
			return ;
		}
		buffer[c] = '\0';
		appender(list, buffer, c);
		free(buffer);
	}
}

void	appender(t_gnl_list **list, char *buffer, int c)
{
	int			i;
	t_gnl_list	*new_n;
	t_gnl_list	*last_n;

	new_n = malloc(sizeof(t_gnl_list));
	if (!new_n)
	{
		list_emptier(list, NULL);
		return ;
	}
	new_n->next = NULL;
	new_n->l_buffer = malloc(sizeof(char) * (c + 1));
	if (!new_n->l_buffer)
	{
		list_emptier(list, &new_n);
		return ;
	}
	i = -1;
	while (buffer[++i] && i < c)
		new_n->l_buffer[i] = buffer[i];
	new_n->l_buffer[i] = '\0';
	if (!(*list))
	{
		*list = new_n;
		return ;
	}
	last_n = ft_lstlast(*list);
	last_n->next = new_n;
}

t_gnl_list	*ft_lstlast(t_gnl_list *list)
{
	t_gnl_list	*node;

	node = list;
	while (node && node->next)
		node = node->next;
	return (node);
}

void	reset_list(t_gnl_list **list)
{
	int			i;
	int			j;
	t_gnl_list	*clean_n;
	t_gnl_list	*last_n;

	i = 0;
	clean_n = malloc(sizeof(t_gnl_list));
	if (!clean_n)
	{
		list_emptier(list, NULL);
		return ;
	}
	clean_n->next = NULL;
	last_n = ft_lstlast(*list);
	clean_n->l_buffer = malloc(sizeof(char) * \
		((ft_strlen(last_n->l_buffer) - i) + 1));
	if (!last_n || !clean_n->l_buffer)
	{
		if (!clean_n->l_buffer)
			list_emptier(list, &clean_n);
		return ;
	}
	j = 0;
	while (last_n->l_buffer[i] && last_n->l_buffer[i] != '\n')
		i++;
	if (last_n->l_buffer && last_n->l_buffer[i] == '\n')
		i++;
	while (last_n->l_buffer[i])
		clean_n->l_buffer[j++] = last_n->l_buffer[i++];
	clean_n->l_buffer[j] = '\0';
	list_emptier(list, NULL);
	*list = clean_n;
}

void	list_emptier(t_gnl_list **list, t_gnl_list **node)
{
	t_gnl_list	*temp;
	t_gnl_list	*next;

	temp = *list;
	if (node)
	{
		free(*node);
		*node = NULL;
	}
	while (temp)
	{
		free(temp->l_buffer);
		next = temp->next;
		free(temp);
		temp = next;
	}
	*list = NULL;
}
