/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_router.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:33:46 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/11 17:23:09 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		letter_printer(t_elem *elem, int fd)
{
	int count;

	count = 0;
	if (is_strchar(elem->argtype) == 0)
	{
		count = ft_strlen((char*)elem->data);
		ft_putstr_fd(elem->data, fd);
	}
	else if (elem->argtype == 's' || elem->argtype == 'S')
		count = string_printer(elem, fd);

	return (count);
}

void	print_routes(t_elem *list, int fd)
{
	int	printed_char;

	printed_char = 0;
	while (list)
	{
		if (is_strchar(list->argtype) == 0)
		{
			//numberhandler
		}
		printed_char += letter_printer(list, fd);
		
		list = list->next;
	}
}

// void	number_handler(t_elem *elem)
// {

// }

int		string_printer(t_elem *elem, int fd)
{
	size_t	string_len;
	int		i;
	char	*temp;
	char	*padding;

	string_len = ft_strlen((const char*)elem->data); // keep this
	// i = 0;
	// if (elem->width && string_len < elem->width)
	// {
	// 	temp = (char*)elem->data;
	// 	padding = ft_strnew(string_len - elem->width);
	// 	while (string_len++ != elem->width)
	// 		padding[i++] = ' ';
	// 	if (ft_strchr(elem->flags, '-'))
	// 		elem->data = ft_strjoin(temp, padding);
	// 	else
	// 		elem->data = ft_strjoin(padding, temp);
	// 	ft_memdel((void**)temp);
	// }


	int count;
	int	to_print;

	count = 0;
	to_print = string_len;
	if (elem->data == NULL && elem->precision == -1)
		return (ft_putstr_part("(null)", 6, fd));
	if (elem->precision != -1 && elem->precision < (int)string_len)
		to_print = elem->precision;
	if (to_print < elem->width && !ft_strchr(elem->flags, '-'))
		count += print_padding(' ', elem->width - to_print, fd); /// ovde praznovo mesto mojt da ne e fiksno da zavisit od dali imat 0 vo flags
	count += ft_putstr_part((const char*)elem->data, to_print, fd);
	if (to_print < elem->width && ft_strchr(elem->flags, '-') != NULL)
		count += print_padding(' ', elem->width - to_print, fd);

	return (count);	
}

int		print_padding(char p, size_t len, int fd)
{
	size_t i;

	i = 0;
	while (i++ < len)
		ft_putchar_fd(p, fd);
	return ((int)i);
}