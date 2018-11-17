/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_router.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 18:33:46 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/16 17:43:09 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

size_t	print_padding(char p, size_t len, int fd)
{
	size_t i;

	i = 0;
	while (i++ < len)
		ft_putchar_fd(p, fd);
	return (len);
}

int		string_printer(t_elem *elem, int fd)
{
	size_t	string_len;
	int		count;
	size_t	to_print;

	if (elem->data == NULL)
		elem->data = ft_strdup("(null)");
	string_len = ft_strlen((const char*)elem->data);
	count = 0;
	to_print = string_len;
	if (elem->precision != -1 && elem->precision < (int)string_len
		&& elem->argtype != '%')
		to_print = elem->precision;
	if (to_print < elem->width && ft_strchr(elem->flags, '-') == NULL)
		count += print_padding(' ', elem->width - to_print, fd);
	count += ft_putstr_part((const char*)elem->data, to_print, fd);
	if (to_print < elem->width && ft_strchr(elem->flags, '-') != NULL)
		count += print_padding(' ', elem->width - to_print, fd);
	return (count);
}

int		char_printer(t_elem *elem, int fd)
{
	int		count;
	char	pad;
	int		dash;

	count = 0;
	dash = (ft_strchr(elem->flags, '-') == NULL ? 0 : 1);
	pad = (ft_strchr(elem->flags, '0') == NULL ? ' ' : '0');
	pad = (dash == 0 ? pad : ' ');
	if (elem->width > 1 && dash == 0)
		count += print_padding(pad, elem->width - 1, fd);
	ft_putchar_fd((char)elem->data, fd);
	count++;
	if (elem->width > 1 && dash)
		count += print_padding(pad, elem->width - 1, fd);
	return (count);
}

int		letter_printer(t_elem *elem, int fd)
{
	int count;

	count = 0;
	if (is_strchar(elem->argtype) == 0 && elem->argtype != '%')
	{
		count = ft_strlen((char*)elem->data);
		ft_putstr_fd(elem->data, fd);
	}
	else if (elem->argtype == 's' || elem->argtype == 'S'
			|| elem->argtype == '%')
		count = string_printer(elem, fd);
	else if (elem->argtype == 'c' || elem->argtype == 'C')
		count = char_printer(elem, fd);
	return (count);
}

size_t	print_routes(t_elem *list, int fd)
{
	int	printed_char;

	printed_char = 0;
	while (list)
	{
		if (is_strchar(list->argtype) == 0 && list->argtype != '%')
		{
			number_handler(list);
		}
		printed_char += letter_printer(list, fd);
		list = list->next;
	}
	return (printed_char);
}
