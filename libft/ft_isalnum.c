/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 08:34:18 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/18 13:56:19 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
checks if the integer that is passed is an alphabet or number.
*/
int	ft_isalnum(char *c)
{
	int	i;

	i = 0;
	while (c[i] && c[i] != '=')
	{
		if (c[i] >= 'a' && c[i] <= 'z')
			i++;
		else if (c[i] == '_')
			i++;
		else if (c[i] >= 'A' && c[i] <= 'Z')
			i++;
		else if (c[i] >= '0' && c[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_isalnum2(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] >= 'a' && c[i] <= 'z')
			i++;
		else if (c[i] >= 'A' && c[i] <= 'Z')
			i++;
		else if (c[i] >= '0' && c[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_charisalnum(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
