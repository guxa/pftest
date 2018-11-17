/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:23:05 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/16 16:46:54 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int			ft_printf(const char *format, ...)
{
	int			charwritten;
	va_list		ap;
	t_elem		*plist;

	charwritten = 0;
	if (!format)
		return (0);
	va_start(ap, format);
	plist = printf_parser(format, ap);
	charwritten = print_routes(plist, 1);
	va_end(ap);
	clear_list(plist);
	return (charwritten);
}
