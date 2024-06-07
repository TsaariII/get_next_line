/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:54:42 by nzharkev          #+#    #+#             */
/*   Updated: 2024/06/07 13:56:13 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_nl(t_gnl_list *list)
{
	int			i;
	t_gnl_list	*line;

	if (!list)
		return (0);
	line = ft_lstlast(list);
	i = 0;
	while (line->l_buffer[i])
	{
		if (line->l_buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	getting_line(t_gnl_list *list, char **next_l)
{
	int	i;
	int	j;
	int	len;

	len = line_till_nl(list);
	*next_l = malloc(sizeof(char) * (len + 1));
	if (!(*next_l))
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->l_buffer[i])
		{
			if (list->l_buffer[i] == '\n')
			{
				(*next_l)[j++] = list->l_buffer[i];
				break ;
			}
			(*next_l)[j++] = list->l_buffer[i++];
		}
		list = list->next;
	}
	(*next_l)[j] = '\0';
}

int	line_till_nl(t_gnl_list *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->l_buffer[i])
		{
			if (list->l_buffer[i] == '\n')
			{
				len++;
				return (len);
			}
			len++;
			i++;
		}
		list = list->next;
	}
	return (len);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static t_gnl_list	*list = NULL;
	char				*next_l;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, &next_l, 0) < 0)
	{
		list_emptier(&list, NULL);
		return (NULL);
	}
	create_list(&list, fd);
	if (!list)
		return (NULL);
	getting_line(list, &next_l);
	reset_list(&list);
	if (next_l && next_l[0] == '\0')
	{
		free(next_l);
		next_l = NULL;
	}
	if (!next_l)
		list_emptier(&list, NULL);
	return (next_l);
}
