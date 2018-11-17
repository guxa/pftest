/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:38:54 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/16 17:55:52 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** setting large 'S' as type here, only to differentiate in clear_list()
*/

t_elem		*add_string_part(char const *inputstr, int start, int end)
{
	char		*cuttedstr;
	t_elem		*new_elem;

	if ((cuttedstr = ft_strsub(inputstr, start, end - start)) == NULL)
		exit_app("strsub in add_string_part returned null");
	if (cuttedstr[0] == '\0')
	{
		ft_memdel((void**)&cuttedstr);
		return (NULL);
	}
	new_elem = create_elem((void*)cuttedstr);
	new_elem->argtype = 'S';
	return (new_elem);
}

t_elem		*create_elem(void *data)
{
	t_elem	*new_element;

	if ((new_element = (t_elem*)malloc(sizeof(t_elem))) == NULL)
		exit_app("Malloc inside create_elem failed");
	new_element->next = NULL;
	new_element->data = data;
	new_element->argtype = '/';
	new_element->flags = ft_strnew(4);
	new_element->length = ft_strnew(2);
	new_element->width = 0;
	new_element->precision = -1;
	return (new_element);
}

void		listadd(t_elem **mainlist, t_elem *newelem)
{
	t_elem *last;

	if (!newelem)
		return ;
	if (*mainlist == NULL)
	{
		*mainlist = newelem;
		return ;
	}
	last = *mainlist;
	while (last->next)
		last = last->next;
	last->next = newelem;
	return ;
}

void		clear_list(t_elem *mainlist)
{
	t_elem *temp;

	if (mainlist == NULL)
		return ;
	temp = mainlist;
	while (mainlist)
	{
		temp = mainlist;
		mainlist = mainlist->next;
		free(temp->flags);
		free(temp->length);
		if (temp->argtype != 'c' && temp->argtype != 'C'
			&& temp->argtype != 's')
			free(temp->data);
		free(temp);
	}
}
