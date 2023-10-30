/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:30:59 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/06 10:11:44 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	count;
	char	*dst_new;
	char	*src_new;

	dst_new = (char *)dst;
	src_new = (char *)src;
	if (!src_new && !dst_new)
		return (0);
	count = 0;
	while (count < n)
	{
		dst_new[count] = src_new[count];
		count++;
	}
	return (dst);
}

/*
if the number is min int or 0, alllocate space for it and call
memcopy to copy the number in string form to the space.
*/
static char	*special_cases(int n, char *arg)
{
	if (n == -2147483648)
	{
		arg = (char *)malloc(12 * sizeof(char));
		return (ft_memcpy(arg, "-2147483648\0", 12));
	}
	else if (n == 0)
	{
		arg = (char *)malloc(2 * sizeof(char));
		return (ft_memcpy(arg, "0\0", 2));
	}
	return (0);
}

/*
allocates space for the number as necessary and then assigns the
charcater version of the numbers accordingly to the allocated string
 in the reverse order.
*/
static char	*gen_arg(int sign, char *arg, int i, int *to_add)
{
	int	j;

	j = 0;
	arg = (char *)malloc((i + 1 + sign) * sizeof(char));
	if (!arg)
		return (0);
	if (sign == 1)
		arg[j++] = '-';
	i--;
	while (i >= 0)
		arg[j++] = to_add[i--] + '0';
	arg[j] = '\0';
	return (arg);
}

/*
first checks for special cases.
if not special case, checks if negative number. then it
stores all the sigits in the number in the reverse order.
then the gen_arg() allocates teh required space and reverses this.
*/
char	*ft_itoa(int n)
{
	int		to_add[20];
	int		i;
	char	*arg;
	int		sign;

	sign = 0;
	arg = 0;
	arg = special_cases(n, arg);
	if (arg == 0)
	{
		if (n < 0)
		{
			sign = 1;
			n = n * (-1);
		}
		i = 0;
		while (n > 0)
		{
			to_add[i++] = n % 10;
			n = n / 10;
		}
		arg = gen_arg(sign, arg, i, to_add);
	}
	return (arg);
}
