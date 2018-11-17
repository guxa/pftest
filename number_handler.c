/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 23:34:25 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/16 17:50:08 by jguleski         ###   ########.fr       */
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
}

/*
** int i e biten i za goleminata na stringot, zs ako precision e 0, nemorat
** +1 byte za tockata da se alocirat elem->precision moram < 0 da go napram
** ~ za da ne vlegvit vo handle_prec, a -2 zaradi vo width logikata za '0' flag
*/

void	float_string(t_elem *elem, intmax_t whole_num, double decimals)
{
	char	*temp;
	char	*result;
	int		i;

	result = ft_itoa(whole_num);
	i = (elem->precision > 0 ? elem->precision + 1 : 0);
	elem->data = ft_strnew(ft_strlen(result) + i);
	ft_strcat(elem->data, result);
	if (elem->precision > 0)
	{
		temp = ft_itoa(decimals);
		ft_strcat(elem->data, ".");
		if ((i = elem->precision - ft_strlen(temp)) != 0)
			while (i-- > 0)
				ft_strcat(elem->data, "0");
		ft_strcat(elem->data, temp);
		free(temp);
		elem->precision = -1;
	}
	free(result);
}

void	handle_floats(t_elem *elem, va_list ap)
{
	intmax_t	whole_num;
	int			i;
	long double	decimals;
	double		incr;

	incr = 0.5;
	if (elem->precision < 0)
		elem->precision = 6;
	i = elem->precision;
	while (i-- > 0)
		incr = incr / 10;
	i = elem->precision + 1;
	if (elem->length[0] == '\0')
		decimals = va_arg(ap, double);
	else if (elem->length[0] == 'l')
		decimals = va_arg(ap, double);
	else
		decimals = va_arg(ap, long double);
	decimals += (decimals < 0 ? -incr : incr);
	whole_num = (intmax_t)(decimals);
	decimals = decimals - whole_num;
	decimals = (decimals < 0 ? -decimals : decimals);
	while (--i)
		decimals = decimals * 10;
	float_string(elem, whole_num, decimals);
}

/*
** ->ovde proverka za == 0 i '#' flag, za da se trgnit, zosto add_hash
** se povikvit posle dodavanje precision, i togas ne se znajt
** dali brojot bil 0, ili od prec se nulite... ->proverkata za < 'X',
** zoso za drugite upper case specifiers U O D undefined beh e length
*/

void	number_handler(t_elem *elem)
{
	int i;

	i = -1;
	if (elem->argtype >= 'A' && elem->argtype < 'X')
	{
		elem->length[0] = '\0';
		elem->length[1] = '\0';
	}
	if (elem->argtype == 'd' || elem->argtype == 'D' || elem->argtype == 'i')
		transform_int(elem);
	else if (elem->argtype != 'f')
		transform_unsigned(elem);
	if ((((char*)elem->data)[0] == '0' || ((char*)elem->data)[0] == '\0')
		&& ft_strchr(elem->flags, '#') && elem->argtype != 'p')
		(ft_strchr(elem->flags, '#'))[0] = '/';
	if (elem->data == NULL)
		exit_app("ova cisto za proverka");
	num_flags_handler(elem);
	if (elem->argtype == 'X')
		while (((char*)elem->data)[++i])
			((char*)elem->data)[i] = ft_toupper(((char*)elem->data)[i]);
}
