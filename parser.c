/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:22:26 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/11 23:46:08 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "printf.h"

int	get_length(const char *format, int start, t_elem *new_elem)
{
	int	num;

	num = 0;
	while (format[start] && is_length(format[start]))
	{
		if (num < 2)
			new_elem->length[num] = format[start];
		num++;
		start++;
	}
	return (num);
}

int process_width_prec(const char *format, int start, t_elem *new_elem, va_list ap)
{
	int	num;

	num = 0;
	if (ft_isdigit(format[start])) // ne proveram dali e '-' zs process_flags ke go zemit
	{
		new_elem->width = ft_atoi(&format[start]);
		num = countdigits(new_elem->width, 10); // naprajv izmena vo countwords za ova: mozen problem ako brojot e 0, dali ke vratit countdigits 1?
	}
	if (format[start] == '*')	// ova e bonus mozda i ne trebit ?
	{
		num++;
		new_elem->width = va_arg(ap, int);
	}
	if (format[start] == '.')
	{
		if (ft_isdigit(format[++start]) == 0)
			new_elem->precision = 0;
		else
			new_elem->precision = ft_atoi(&format[start]); // mozda ke ni trebit uslov za ako e - precision da go smenime vo 0
		num = 1 + countdigits(new_elem->precision, 10); // ovde 1 + za tockata
	}

	return (num);
}

int	process_flags(const char *format, int start, t_elem *new_elem)
{
	int	countflags;

	countflags = 0;
	while (is_flag(format[start]))
	{
		//mozda da se dodajt strchr proverka za ako go imat nekoj flag dva pati da ne go dodavame
		new_elem->flags[countflags] = format[start];
		countflags++;
		start++;
	}
	return (countflags);
}

int	format_data(t_elem **list, const char *format, va_list ap, int pos)
{
	t_elem	*new;

	new = create_elem(NULL);
	if (is_flag(format[pos]))
		pos += process_flags(format, pos, new);
	if (format[pos] == '*' || ft_isdigit(format[pos]))
		pos += process_width_prec(format, pos, new, ap);
	if (format[pos] == '.')
		pos += process_width_prec(format, pos, new, ap);
	if (format[pos] && is_length(format[pos]))
		pos += get_length(format, pos, new);
	if (format[pos] && is_printvar(format[pos] == 0)) // ova mozda error trebit da frlit?
		exit_app("Invalid specifier\n usage: ft_printf %%[flags][width][.precision][length]specifier");
	if (format[pos])
	{
		new->argtype = format[pos];
		pos++;
		new->data = (new->argtype != '%' ? va_arg(ap, void*) : ft_strdup("%")); // ili null
		new->is_arg = 1; // ova ne znam so uloga bi imalo ali ajde
	}
	listadd(list, new);
	return (pos);
}

t_elem		*printf_parser(const char *format, va_list ap)
{
	int			count;
	int			position;
	t_elem		*list;

	count = 0;
	position = 0;
	list = NULL;
	while (format[count])
	{
		if (format[count] == '%')
		{
			listadd(&list, add_string_part(format, position, count));
			count++;
			count = format_data(&list, format, ap, count);
			position = count;
		}
		if (format[count] != '%' && format[count])
			count++;
	}
	listadd(&list, add_string_part(format, position, count));
	return (list);
}