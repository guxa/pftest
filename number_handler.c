/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 23:34:25 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/12 18:00:37 by jguleski         ###   ########.fr       */
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



// void	add_padding(t_elem *elem, int justify, char pad)
// {
// 	char	pad;
// 	int		justify;

// 	pad = ' ';
// 	justify = 0;
// 	if (ft_strchr(elem->flags, '-'))
// 		justify = 1;
// 	if (ft_strchr(elem->flags, '0'))
// 		pad = '0';
// }

void	handle_prec(t_elem *elem, int digits)
{
	int		diff;
	char	*temp;
	int		sign;

	sign = 0;
	// if (ft_strchr(elem->flags, '+') || ft_strchr(elem->flags, ' '))
	// 	sign++;
	if (ft_isdigit(((char*)(elem->data))[0]) == 0)
		sign++;
	diff = elem->precision - (digits - sign);
	temp = ft_strnew(elem->precision + sign);  // + sign za ako imat + ili ' '
	ft_strcpy(&temp[diff], (const char*)elem->data); // + sign za da ne go kopirame minusot ako imat
	while (--diff + sign >= 0)
		temp[diff + sign] = '0';
	if (sign)
		temp[0] = '-';
	// if (sign)
	// {
	// 	if (((char *)(elem->data))[0] != '-' && ft_strchr(elem->flags, '+'))
	// 		temp[0] = '+';
	// 	else if (((char *)(elem->data))[0] != '-' && ft_strchr(elem->flags, ' '))
	// 		temp[0] = ' ';
	// }
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
	if (ft_strchr(elem->flags, '+'))
	{
		if (ft_strchr((char *)(elem->data), '-') == NULL)
			temp = ft_strjoin("+", (const char *)elem->data);
	}
	else if (ft_strchr(elem->flags, ' '))
		if (ft_strchr((char *)(elem->data), '-') == NULL)
			temp = ft_strjoin(" ", (const char*)elem->data);
	if (temp)
	{
		ft_memdel(&(elem->data));
		elem->data = (void*)temp;
	}
	//add_padding(elem);
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