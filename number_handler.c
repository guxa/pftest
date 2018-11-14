/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 23:34:25 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/13 22:16:50 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"


void	transform_int(t_elem *elem)
{
	intmax_t	number;

	number = (intmax_t)elem->data; 
	if (number == 0)
		elem->data = (elem->precision == 0 ? ft_strdup("") : ft_strdup("0"));
	else if (elem->length[0] == '\0' && elem->argtype != 'D')
		elem->data = ft_itoa((int)number);
	else if (elem->length[0] == 'h' && elem->length[1] == 'h')
		elem->data = ft_itoa((char)number);
	else if (elem->length[0] == 'h')
		elem->data = ft_itoa((short)number);
	else if (elem->length[0] == 'l' && elem->length[1] == 'l')
		elem->data = ft_itoa((long long)number);
	else if (elem->length[0] == 'l' || elem->argtype == 'D')
		elem->data = ft_itoa((long)number);
	else if (elem->length[0] == 'z')
		elem->data = ft_itoa((size_t)number);
	else if (elem->length[0] == 'j')
		elem->data = ft_itoa((intmax_t)number);
}

void	transform_unsigned(t_elem *elem)
{
	uintmax_t	number;
	int			base;

	number = (uintmax_t)elem->data;
	base = getbase(elem->argtype);
	if (number == 0)
		elem->data = (elem->precision == 0 ? ft_strdup("") : ft_strdup("0"));
	else if (elem->argtype == 'p')
		elem->data = unsigned_itoa((unsigned long)elem->data, 16);
	else if (elem->length[0] == '\0')
		elem->data = unsigned_itoa((unsigned int)elem->data, base);
	else if (elem->length[0] == 'h' && elem->length[1] == 'h')
		elem->data = unsigned_itoa((unsigned char)elem->data, base);
	else if (elem->length[0] == 'h')
		elem->data = unsigned_itoa((unsigned short)elem->data, base);
	else if (elem->length[0] == 'l' && elem->length[1] == 'l')
		elem->data = unsigned_itoa((unsigned long long)elem->data, base);
	else if (elem->length[0] == 'l')
		elem->data = unsigned_itoa((unsigned long)elem->data, base);
	else if (elem->length[0] == 'z')
		elem->data = unsigned_itoa((size_t)elem->data, base);
	else if (elem->length[0] == 'j')
		elem->data = unsigned_itoa((uintmax_t)elem->data, base);
	// if (elem->argtype == 'X')
	//  	ft_strmap(elem->data, ft_toupper);
}


void	add_padding(t_elem *elem, int sign)
{
	char	pad;
	int		justify;
	int		diff;
	char	*padding;
	char	*temp;

	pad = ' ';
	justify = (ft_strchr(elem->flags, '-') == NULL ? 0 : 1);
	if ((diff = (int)elem->width - (int)ft_strlen((char*)elem->data)) < 1)
		return ;
	if (ft_strchr(elem->flags, '0') && justify == 0 && elem->precision == -1) // za precis ovde ne sum sig
		pad = '0';
	if (pad == ' ')
		sign = 0;
	padding = ft_strnew(diff + sign);
	while (--diff >= 0)
		padding[diff + sign] = pad;
	padding[0] = (sign == 1 ? ((char*)elem->data)[0] : pad);
	if (justify)
		temp = ft_strjoin(elem->data, padding);
	else
		temp = ft_strjoin(padding, elem->data + sign);
	free(padding);
	ft_memdel(&(elem->data));
	elem->data = temp;
}

void	handle_prec(t_elem *elem, int digits, int sign)
{
	int		diff;
	char	*temp;
	// int		sign;

	// sign = 0;
	// if (ft_isdigit(((char*)(elem->data))[0]) == 0)
	// 	sign++;
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
	int		sign;

	temp = NULL;
	sign = (((char*)(elem->data))[0] == '-' ? 1 : 0); // nemat mesto vo width ama evo i ovde najde primena
	length = ft_strlen((const char*)elem->data);
	if (elem->precision > -1 && elem->precision > length - sign)
		handle_prec(elem, length, sign);
	if (ft_strchr(elem->flags, '+') && is_signed(elem->argtype)	&& !sign)
	{
		temp = ft_strjoin("+", (const char *)elem->data);
		sign = 1;
	}
	else if (ft_strchr(elem->flags, ' ') && is_signed(elem->argtype) && !sign)
	{
		temp = ft_strjoin(" ", (const char*)elem->data);
		sign = 1;
	}
	if (temp)
	{
		ft_memdel(&(elem->data));
		elem->data = (void*)temp;
	}
	add_padding(elem, sign);
	add_hash(elem);
}

void	number_handler(t_elem *elem)
{
	if (elem->argtype >= 'A' && elem->argtype < 'X')
	{
		elem->length[0] = '\0';
		elem->length[1] = '\0';
	}
	if (elem->data == 0 && ft_strchr(elem->flags, '#')) //&&getbase(elem->argtype) != 10
		(ft_strchr(elem->flags, '#'))[0] = '/';
	if (elem->argtype == 'd' || elem->argtype == 'D' || elem->argtype == 'i')
		transform_int(elem);
	else if (elem->argtype == 'x' || elem->argtype == 'X' || elem->argtype == 'p'
			|| elem->argtype == 'o' || elem->argtype == 'O' || elem->argtype == 'u'
			|| elem->argtype == 'U')
		transform_unsigned(elem);
	if (elem->data == NULL)
		exit_app("ova cisto za proverka");
	num_flags_handler(elem);
}

void	add_hash(t_elem *elem)
{
	int		hash;
	char	*temp;
	char	*result;
	int		spaces;

	spaces = 0;
	hash = 0;
	temp = NULL;
	if (ft_strchr(elem->flags, '#') && getbase(elem->argtype) != 10)
		hash = 1;
	//	hash = (((char *)elem->data)[0] == '0' ? 0 : 1);
	if (hash)
	{
		while (((char*)elem->data)[spaces] == ' ')
			spaces++;
		if (elem->argtype == 'X' || elem->argtype == 'x')
			hash++;
		temp = ft_strnew(hash + spaces);
		ft_strncpy(temp, (const char*)elem->data, spaces);
		ft_strncpy(temp, "0x", hash);
		result = ft_strjoin(temp, &(elem->data[spaces]));
		temp = elem->data;
		elem->data = result;
		ft_memdel((void **)&temp);
	}
}

/*
converts a signed integer into decimal representation [-]dddd.
Precision specifies the minimum number of digits to appear. 
The default precision is 1.
If both the converted value and the precision are ​0​ the conversion 
results in no characters.


error: flag '#' results in undefined behavior with 'd' conversion specifier
*/