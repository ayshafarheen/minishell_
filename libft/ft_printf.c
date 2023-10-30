/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:26:57 by afarheen          #+#    #+#             */
/*   Updated: 2022/12/03 14:02:06 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
For strings and characters
If for string the string passed is null, write "(null)" or write as is, if
it is a character, write the character.
*/
static int	string_and_char(const char *str, va_list argptr)
{
	char	ch;
	char	*a;

	if (ft_strncmp(str, "%s", 2) == 0)
	{
		a = va_arg(argptr, char *);
		if (!a)
			return (write(1, "(null)", 6));
		return (write(1, a, ft_strlen(a)));
	}
	else
	{
		ch = va_arg(argptr, int);
		return (write(1, &ch, 1));
	}
}

/*
check which format is being called for and call the required function
*/
static int	check_cases(const char *str, va_list argptr)
{
	int		flag;

	flag = 0;
	if (ft_strncmp(str, "%d", 2) == 0 || ft_strncmp(str, "%i", 2) == 0)
		return (ft_putnbr(va_arg(argptr, int), "0123456789"));
	if (ft_strncmp(str, "%s", 2) == 0 || ft_strncmp(str, "%c", 2) == 0)
		return (string_and_char(str, argptr));
	else if (ft_strncmp(str, "%p", 2) == 0)
		return (write(1, "0x", 2)
			+ ft_putnbr_base(va_arg(argptr, size_t), "0123456789abcdef", 0));
	else if (ft_strncmp(str, "%X", 2) == 0)
		return (ft_putnbr_base(va_arg(argptr, unsigned int),
				"0123456789ABCDEF", 0));
	else if (ft_strncmp(str, "%x", 2) == 0)
		return (ft_putnbr_base(va_arg(argptr, unsigned int),
				"0123456789abcdef", 0));
	else if (ft_strncmp(str, "%%", 2) == 0)
		return (write(1, "%", 1));
	else if (ft_strncmp(str, "%u", 2) == 0)
		return (ft_putnbr_base(va_arg(argptr, unsigned int), "0123456789", 0));
	return (flag);
}

/*
take in a string and multiple other arguments.
if the function encounters a "%", it goes to the check function.
if not, it writes the charcater as is.
*/
int	ft_printf(const char *str, ...)
{
	va_list	argptr;
	int		i;
	int		flag;

	va_start(argptr, str);
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			flag += check_cases(&str[i], argptr);
			i = i + 2;
		}
		else
		{
			write(1, &str[i], 1);
			flag++;
			i++;
		}
	}
	va_end(argptr);
	return (flag);
}
