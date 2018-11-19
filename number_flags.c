/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:37:16 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/18 18:29:21 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** sign is sent to know if there is + or - in the string, and is made to 0 if
** pad == ' ', cause when the padding is ' ' the sign stays attached to thefirst
** "number" of the string in elem->data. But if pad == '0' then sign is moved
** at the beggining of the padding so "-12" with width 5 becomes "-0012".
** -> If a precision is given with a numeric conversion the '0' flag is ignored
*/

void	add_padding(t_elem *elem, int sign, int hash)
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
	if (ft_strchr(elem->flags, '0') && justify == 0 && elem->precision == -1)
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
		temp = insert_string(padding, elem->data + sign, hash, pad);
	free(padding);
	ft_memdel(&(elem->data));
	elem->data = temp;
}

void	handle_prec(t_elem *elem, int digits, int sign)
{
	int		diff;
	char	*temp;

	diff = elem->precision - (digits - sign);
	temp = ft_strnew(elem->precision + sign);
	ft_strcpy(&temp[diff], (const char*)elem->data);
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
	sign = (((char*)(elem->data))[0] == '-' ? 1 : 0);
	length = ft_strlen((const char*)elem->data);
	if (elem->precision > -1 && elem->precision > length - sign)
		handle_prec(elem, length, sign);
	if (ft_strchr(elem->flags, '+') && is_signed(elem->argtype) && !sign)
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
	add_padding(elem, sign, add_hash(elem));
}

int		add_hash(t_elem *elem)
{
	int		hash;
	char	*temp;
	char	*result;
	int		base;

	hash = 0;
	temp = NULL;
	base = getbase(elem->argtype);
	if (base != 10 && (ft_strchr(elem->flags, '#') || elem->argtype == 'p'))
		if ((base == 8 && ((char*)elem->data)[0] == '0') == 0)
			if ((base == 16 && ((char*)elem->data)[0] == '\0') == 0)
				hash = 1;
	if (hash)
	{
		if (base == 16)
			hash++;
		temp = ft_strnew(hash);
		ft_strncpy(temp, "0x", hash);
		result = ft_strjoin(temp, elem->data);
		ft_memdel((void **)&temp);
		free(elem->data);
		elem->data = result;
	}
	return (hash);
}
