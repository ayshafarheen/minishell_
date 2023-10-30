/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:35:26 by afarheen          #+#    #+#             */
/*   Updated: 2023/01/23 14:56:47 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
recursively calls the function itself to print the number from the start.
each time that it is called it is called with an incremented flag to account
for the extra number being printed and the flag is set to the return as
well each time its called. when the number becomes 0, it stops entering
the loop so the first number is written then onwards.
*/
static int	regular_number(long int nbr, char *base, int flag)
{
	if (nbr)
	{
		flag = regular_number(nbr / 10, base, flag + 1);
		write(1, &base[nbr % 10], 1);
	}
	if (nbr == 0 && flag == 0)
		flag += write(1, &base[0], 1);
	return (flag);
}

/*
the starting funciton for regular_number, just checks if the number is 0
or below 0 and does the required.
*/
int	ft_putnbr(long int nbr, char *base)
{
	int	flag;

	flag = 0;
	if (nbr == 0)
		return (write(1, "0", 1));
	if (nbr < 0)
	{
		flag += write(1, "-", 1);
		nbr = nbr *(-1);
	}
	return (flag + regular_number(nbr, base, 0));
}

/*
same as regular_number but wih size_t and variable base length instead.
*/
int	ft_putnbr_base(size_t nbr, char *base, int flag)
{
	int	len;

	len = ft_strlen(base);
	if (nbr)
	{
		flag = ft_putnbr_base(nbr / len, base, flag + 1);
		write(1, &base[nbr % len], 1);
	}
	if (nbr == 0 && flag == 0)
		flag += write(1, &base[0], 1);
	return (flag);
}
