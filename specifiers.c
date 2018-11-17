/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifiers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 22:37:43 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/16 17:56:29 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int			is_printvar(char c)
{
	if (c == 's' || c == 'c' || c == 'd' || c == 'i' || c == '%' || c == 'f'
			|| c == 'p' || c == 'o' || c == 'u' || c == 'x' || c == 'S'
			|| c == 'C' || c == 'X' || c == 'U' || c == 'O' || c == 'D')
		return (1);
	return (0);
}

int			is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
		return (1);
	return (0);
}

int			is_length(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == '0' || c == 'L')
		return (1);
	return (0);
}

int			is_signed(char c)
{
	if (c == 'd' || c == 'D' || c == 'i' || c == 'f')
		return (1);
	return (0);
}

int			is_strchar(char c)
{
	if (c == 'c' || c == 'C' || c == 's' || c == 'S')
		return (1);
	return (0);
}
