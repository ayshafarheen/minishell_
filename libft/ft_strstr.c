/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalshebl <nalshebl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:31:56 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/16 22:44:02 by nalshebl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	if (to_find[0] == 0)
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		temp = i;
		while (str[temp] == to_find[j] && str[temp] != '\0')
		{
			j++;
			temp++;
			if (to_find[j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (0);
}
