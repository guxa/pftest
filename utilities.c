/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:51:15 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/14 15:07:56 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void		exit_app(const char *source)
{
	b_printf("%s\n", source);
	exit(1);
}

int			getbase(char spec)
{
	if (spec == 'x' || spec == 'X' || spec == 'p')
		return (16);
	if (spec == 'o' || spec == 'O')
		return (8);
	else
		return (10);
}

char	*insert_string(char *to_insert, char *dest, int position, char pad)
{
	char	*temp;

	if (position == 0 || pad == ' ')
		return (ft_strjoin(to_insert, dest));
	temp = ft_strnew(ft_strlen(to_insert) + ft_strlen(dest));
	ft_strncpy(temp, dest, position);
	ft_strcat(temp, to_insert);
	ft_strcat(temp, &(dest[position]));
	return (temp);
	//ft_strcpy(&temp[hash], to_insert);
}

int		ft_putstr_part(char const *str, int size, int fd)
{
	int count;

	count = 0;
	if (!str)
		return (0);
	while (str[count] && count < size)
		ft_putchar_fd(str[count++], fd);
	return (count);
}