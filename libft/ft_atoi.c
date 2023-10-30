/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:35:06 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/16 14:19:42 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
takes in string and skips through all the spaces and checks whether the
number is positive or negative. it then goes through the numbers in the
string one by one and calculates the number which is finally returned.
if the number is greater than max long, -1 is returned. if it is less
than min int, 0 is returned.
*/
int	ft_atoi(const char *str)
{
	int					i;
	int					minus;
	unsigned long long	nbr;

	i = 0;
	minus = 1;
	nbr = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i = i + 1;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			minus = -1;
		i = i + 1;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i++] - '0');
		if (nbr >= 9223372036854775807 && minus == 1)
			return (-1);
		if (nbr > 9223372036854775807 && minus == -1)
			return (0);
	}
	return (minus * (int)nbr);
}
