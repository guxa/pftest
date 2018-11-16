/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:23:05 by jguleski          #+#    #+#             */
/*   Updated: 2018/11/15 23:45:45 by jguleski         ###   ########.fr       */
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
	return (charwritten);
}


// A format specifier follows this prototype: [see compatibility note below] 
// %[flags][width][.precision][length]specifier

// int main()
// {
// 	char *str2;
// 	int i;

// 	i = 0;
// 	str2 = "satot e 5:15";
// 	//ft_printf("test jane %5dbla %.12s", 100, str2);

// 	// printf("Original: test %d\n", 192);
// 	// printf("Precision:\n");
// 	// printf("test %%.6d: %.6d\n", 192);
// 	// printf("test %%17.d: %17.d\n", 192);
// 	// printf("test %%.*d: %.*d\n", 7, 192);

// 	// printf("\nWIDTH and precision string:\n");
// 	// i = printf("10.3s	test: %10.3s\n", str2);
// 	// printf("%%.s	test: %.s\n", str2);
// 	// printf("%%.5s	test: %.5s\n", str2);
// 	// printf("%%10.3s	null test: %10.3s\n", NULL);

// 	// ft_printf("\n>>>>>>>my ft_printf:\n");
// 	// i = ft_printf("10.3s	test: %10.3s\n", str2);

// 	// printf("\nWIDTH and precision CHAR:\n");
// 	// i = printf("-10c	test: %-10c end\n", str2[0]);
// 	// i = printf("%%c	test: %c end\n", 0);
// 	// i = printf("5c	test: %5c end\n", str2[0]);

// 	//ft_printf("^.^/%#54.24zo^.^/", -2067268156);
// 	ft_printf(">------------<%31.48ls>------------<", NULL);
// 	float testf = -1.200050; //5.02345062345;
// 	double testf2 = 1.200000;
// 	long double testf3 = 1.2000055;
// 	printf("%%10f test:%10f\n", testf);
// 	printf("%%10.3f test:%10.3f\n", testf);
// 	printf("%%-10f test:%-10f\n", testf);
// 	printf("%%+-10f test:%+-10f\n\n", testf);

// 	ft_printf("%%10f test:%10f\n", testf);
// 	ft_printf("%%10.3f test:%10.3f\n", testf);
// 	ft_printf("%%-10f test:%-10f\n", testf);
// 	ft_printf("%%+-10f test:%+-10f\n\n", testf);

// 	printf("%%lf test:%lf\n", testf2);
// 	printf("%%Lf test:%Lf\n", testf3);
// 	printf("printf UP^ <><><> MY ft_printf DOWN:\n");
// 	ft_printf("%%f test:%f\n", testf);
// 	ft_printf("%%lf test:%lf\n", testf2);
// 	ft_printf("%%Lf test:%Lf\n", testf3);

// 	// printf("%%.9f test:%.f\n", testf);
// 	// printf("%%.9lf test:%lf\n", testf2);
// 	// printf("%%Lf test:%Lf\n", testf3);

// 	// t_elem *elem = malloc(sizeof(t_elem));
// 	// elem->precision = 0;
// 	// elem->data = &testf;
// 	// elem->length = ft_strnew(2);
// 	// handle_floats(elem);
// 	// elem->data = &testf3;
// 	// elem->length[0] = 'L';
// 	// handle_floats(elem);

// 	// printf("\n>>>>>>>d & i tests:\n");
// 	// ft_printf("S :%S\n", "@@");
// 	// ft_printf("test %.0% :%03.X\n", 720306);
// 	// // ft_printf("Pointer test:%10hhp\n", 455);
// 	// // printf("ORG Pointer test:%10hhp\n", 455);
// 	// // ft_printf("MY Pointer test:%10hp\n", 1);
// 	// // printf("ORG Pointer test:%10hp\n", 1);
// 	// printf("Pointer test:%3p\n", (void *)1);
// 	// //ft_printf("test:%#3jx\n", 0); // %#.3jx,16 %#-+03jx
// 	// //i = ft_printf("U test - MY printf:%u\n", 4294967296);
// 	// //i = printf("U test - org printf:%u\n", 4294967296);

// 	// ft_printf("hd test:%hd\n", (short)-3455);
// 	// ft_printf("hhd test:%hhd\n", (char)-3455);
// 	// ft_printf("ld test:%ld\n", (long)2147483647);
// 	// ft_printf("lld test:%lld\n", (long long)2147483647);
// 	// ft_printf("jd test:%jd\n", (intmax_t)2147483647);
// 	// ft_printf("zd test:%zd\n", (size_t)2147483647);
// }

/* 		>>>>>>>>	PRECISION	<<<<<<<<
	If the precision is given as just '.', or the precision is negative,
the precision is taken to be zero. 

// negativen broj kaj precision e error: invalid covnersion specifier

// so 0 precision, ne printat nieden karakter od stringot

// error: precision used with 'c' conversion specifier, 
resulting in undefined behavior

// za char ako e 0, niso ne printat

// za brojki, minimum number of digits to be printed, drugite 0 gi prajt

*/

/*		>>>>>>>>	WIDTH	<<<<<<<<
	If the converted value has fewer characters than the field width, 
it will be padded with spaces on the left (or right, if the 
left-adjustment flag has been given).

	A negative field width is taken as a '-' flag followed by a positive 
 field width. In no case does a nonexistent or small field width cause 
 truncation of a field; if the result of a conversion is wider than 
 the field width, the field is expanded to contain the conversion result.
*/


/*		>>>>>>>>	FLAGS	<<<<<<<<

' ' - ako nemat znak, '-' ili '+' togas prazno mesto ke stajt pred brojkata
	so znacit ako iamt + ova ne vazit
+  - stavat znak pred brojkata duri i pozitiven broj da e

# - samo za  o, x or X - the value is preceeded with 0, 0x or 0X respectively for values different than zero
The value should be converted to an "alternate form". For o conversions, the first character of the output
string is made zero
(by prefixing a 0 if it was not zero already). For x and X conversions,
a nonzero result has the string "0x" (or "0X" for X conversions) prepended to it.

%#.3jx,16,[0x010],5,[010],3
za X i x, samo ako e 0 vrednosta ne se dodavat 0x, a ako prvata cifra 0 ama od precision
togas se dodavat

a za O neznam
-------

0 - 
{
Left-pads the number with zeroes (0) instead of spaces when padding is
specified.	If the 0 and - flags both appear, the 0 flag is ignored. 
	If a precision is given with a numeric conversion (d, i, o, u, x, and X),
 	the 0 flag is ignored.
} 	


/// Ako imat precision, znakot e najlevo, pred nulite od precision,
/// ako nemat precision, a imat width, znakot e standard odma do brojkata
		OSVEN ako imat 0 flag, togas pak e na pocetok


Tests from 59 to 2715 se ok

%#.3jx,16,[0x010],5,[010],3   -> problematicen to solve

prvo dodavat 0 za precision posle append 0x
za width?
*/