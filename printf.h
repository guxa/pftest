/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 22:25:49 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/22 18:24:31 by jguleski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include "libft/includes/libft.h"

typedef struct	s_pelement
{
	void				*data;
	char				*flags;
	size_t				width;
	int					precision;
	char				*length;
	char				argtype;
	struct s_pelement	*next;
}				t_elem;

void			clear_list(t_elem *mainlist);
int				ft_printf_fd(int fd, const char *format, ...);
int				ft_printf(const char *format, ...);
void			handle_floats(t_elem *elem, va_list ap);
void			num_flags_handler(t_elem *elem);
char			*insert_string(char *to_insert, char *dest, int hash, char pad);
int				add_hash(t_elem *elem);
int				getbase(char spec);
void			number_handler(t_elem *elem);
size_t			print_routes(t_elem *list, int fd);
char			*unsigned_itoa(uintmax_t number, int base);
int				un_countdigits(uintmax_t number, int base);

int				ft_putstr_part(char const *str, int n, int fd);
int				is_printvar(char c);
int				is_flag(char c);
int				is_length(char c);
int				is_strchar(char c);
int				is_signed(char c);

t_elem			*add_string_part(char const *inputstr, int start, int end);
void			listadd(t_elem **mainlist, t_elem *newelem);
int				countdigits(intmax_t number, int base);
t_elem			*create_elem(void *data);
t_elem			*printf_parser(const char *format, va_list ap);
void			exit_app(const char *source);

#endif
