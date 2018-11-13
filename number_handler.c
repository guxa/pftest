/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 23:34:25 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/12 20:23:14 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"


void	transform_int(t_elem *elem)
{
	intmax_t	number;

	number = (intmax_t)elem->data;

	if (elem->length[0] == '\0')
		elem->data = ft_itoa((int)number);
	else if (elem->length[0] == 'h' && elem->length[1] == 'h')
		elem->data = ft_itoa((char)number);
	else if (elem->length[0] == 'h')
		elem->data = ft_itoa((short)number);
	else if (elem->length[0] == 'l' && elem->length[1] == 'l')
		elem->data = ft_itoa((long long)number);
	else if (elem->length[0] == 'l')
		elem->data = ft_itoa((long)number);
	else if (elem->length[0] == 'z')
		elem->data = ft_itoa((size_t)number);
	else if (elem->length[0] == 'j')
		elem->data = ft_itoa((intmax_t)number);
}



void	add_padding(t_elem *elem)
{
	char	pad;
	int		justify;
	int		diff;
	char	*padding;
	char	*temp;

	pad = ' ';
	justify = 0;
	diff = (int)elem->width - (int)ft_strlen((char*)elem->data);
	if (diff < 1)
		return ;
	if (ft_strchr(elem->flags, '-'))
		justify = 1;
	if (ft_strchr(elem->flags, '0') && justify == 0 && elem->precision == -1)
		pad = '0';
	padding = ft_strnew(diff);
	while (--diff >= 0)
		padding[diff] = pad;
	if (justify)
		temp = ft_strjoin(elem->data, padding);
	else
		temp = ft_strjoin(padding, elem->data);
	free(padding);
	ft_memdel(&(elem->data));
	elem->data = temp;
}

void	handle_prec(t_elem *elem, int digits)
{
	int		diff;
	char	*temp;
	int		sign;

	sign = 0;
	if (ft_isdigit(((char*)(elem->data))[0]) == 0)
		sign++;
	diff = elem->precision - (digits - sign);
	temp = ft_strnew(elem->precision + sign);  // + sign za ako imat + ili ' '
	ft_strcpy(&temp[diff], (const char*)elem->data); // + sign za da ne go kopirame minusot ako imat
	while (--diff + sign >= 0)
		temp[diff + sign] = '0';
	if (sign)
		temp[0] = '-';
	ft_memdel(&(elem->data));
	elem->data = (void*)temp;
}

void	num_flags_handler(t_elem *elem)
{
	int		length;
	char	*temp;

	temp = NULL;
	length = ft_strlen((const char*)elem->data);
	if (elem->precision > -1 && elem->precision > length)
		handle_prec(elem, length);
	if (ft_strchr(elem->flags, '+') && is_signed_conv(elem->argtype))
	{
		if (ft_strchr((char *)(elem->data), '-') == NULL)
			temp = ft_strjoin("+", (const char *)elem->data);
	}
	else if (ft_strchr(elem->flags, ' ') && is_signed_conv(elem->argtype))
		if (ft_strchr((char *)(elem->data), '-') == NULL)
			temp = ft_strjoin(" ", (const char*)elem->data);
	if (temp)
	{
		ft_memdel(&(elem->data));
		elem->data = (void*)temp;
	}
	add_padding(elem);
}

void	number_handler(t_elem *elem)
{
	if (elem->argtype == 'd' || elem->argtype == 'D' || elem->argtype == 'i')
		transform_int(elem);

	num_flags_handler(elem);
}

/*
converts a signed integer into decimal representation [-]dddd.
Precision specifies the minimum number of digits to appear. 
The default precision is 1.
If both the converted value and the precision are ​0​ the conversion 
results in no characters.


error: flag '#' results in undefined behavior with 'd' conversion specifier
*/