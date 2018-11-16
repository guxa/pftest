/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 13:27:07 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/15 00:43:23 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*newstr;

	newstr = (char *)malloc(sizeof(char) * size + 1);
	if (newstr == NULL)
		return (NULL);
	newstr[size] = '\0';
	while (size--)
		newstr[size] = 0;
	return (newstr);
}
