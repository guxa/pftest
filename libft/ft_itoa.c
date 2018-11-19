/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 18:17:34 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/18 17:58:53 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(intmax_t number, int base)
{
	int			size;
	uintmax_t	newnumber;
	char		*numtable;
	char		*string;

	numtable = "0123456789abcdef";
	size = countdigits(number, base);
	newnumber = (number > 0 ? number : -number);
	if (number < 0 && base == 10)
		size++;
	string = ft_strnew((size > 0 ? size : 1));
	if (!string)
		return (NULL);
	(string ? string[0] = '0' : 0);
	while (size > 0)
	{
		string[--size] = numtable[newnumber % base];
		newnumber = newnumber / base;
	}
	if (number < 0 && base == 10)
		string[0] = '-';
	return (string);
}

int		countdigits(intmax_t number, int base)
{
	int size;

	size = 0;
	if (number == 0)
		return (1);
	while (number)
	{
		size++;
		number = number / base;
	}
	return (size);
}

char	*ft_itoa(intmax_t n)
{
	return (ft_itoa_base(n, 10));
}

int		un_countdigits(uintmax_t number, int base)
{
	int size;

	size = 0;
	if (number == 0)
		return (1);
	while (number)
	{
		size++;
		number = number / base;
	}
	return (size);
}

char	*unsigned_itoa(uintmax_t number, int base)
{
	int			size;
	char		*numtable;
	char		*string;

	numtable = "0123456789abcdef";
	size = un_countdigits(number, base);
	string = ft_strnew((size > 0 ? size : 1));
	if (!string)
		return (NULL);
	(string ? string[0] = '0' : 0);
	while (size > 0)
	{
		string[--size] = numtable[number % base];
		number = number / base;
	}
	return (string);
}
