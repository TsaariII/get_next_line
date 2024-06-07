/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:56:00 by nzharkev          #+#    #+#             */
/*   Updated: 2024/06/07 10:55:54 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_gnl_list
{
	char				*l_buffer;
	struct s_gnl_list	*next;
}	t_gnl_list;

char		*get_next_line(int fd);
int			find_nl(t_gnl_list *list);
int			ft_strlen(char *str);
int			line_till_nl(t_gnl_list *list);
t_gnl_list	*ft_lstlast(t_gnl_list *list);
void		appender(t_gnl_list **list, char *buffer, int c);
void		create_list(t_gnl_list **list, int fd);
void		list_emptier(t_gnl_list **list, t_gnl_list **node);
void		getting_line(t_gnl_list *list, char **next_l);
void		reset_list(t_gnl_list **list);

#endif