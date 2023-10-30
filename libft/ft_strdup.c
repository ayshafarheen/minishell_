/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalshebl <nalshebl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:37:50 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/16 22:44:33 by nalshebl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	count;

	count = 0;
	while (src[count] != '\0')
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}

char	*ft_strndup(const char *src, int n)
{
	char	*copy;

	if (!src)
		return (0);
	copy = (char *)malloc(n + 1);
	if (!copy)
		return (0);
	ft_strncpy(copy, (char *)src, n);
	copy[n] = 0;
	return (copy);
}

/*
Allocate space for the length of the string passed including space for null
terminator and then copy the string to the new space.
*/
char	*ft_strdup(const char *src)
{
	char	*copy;

	if (!src)
		return (0);
	copy = (char *)malloc(ft_strlen(src) + 1);
	if (!copy)
		return (0);
	ft_strcpy(copy, (char *)src);
	return (copy);
}
