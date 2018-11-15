/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:38:54 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/14 17:51:55 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

// t_elem	*newlistelem(char const *inputstr, int start, int end)
// {
// 	char		*cuttedstr;
// 	t_elem	*templist;

// 	templist = NULL;
// 	cuttedstr = cutstr(inputstr, start, end);
// 	if (!cuttedstr)
// 		return (NULL);
// 	if ((templist = (t_elem*)malloc(sizeof(t_elem))))
// 	{
// 		templist->next = NULL;
// 		templist->is_arg = 0;
// 		templist->param = cuttedstr;
// 		templist->argtype = 's';
// 		return (templist);
// 	}
// 	return (NULL);
// }

t_elem	*add_string_part(char const *inputstr, int start, int end)
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
	new_elem->argtype = 's';
	return (new_elem);
}

t_elem	*create_elem(void *data)
{
	t_elem	*new_element;

	if ((new_element = (t_elem*)malloc(sizeof(t_elem))) == NULL)
		exit_app("Malloc inside create_elem failed");
	new_element->next = NULL;
	new_element->is_arg = 0;
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