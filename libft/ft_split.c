/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalshebl <nalshebl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:27:48 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/16 22:45:07 by nalshebl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_size(const char *s, char c)
{
	int	i;
	int	index;
	int	length;

	length = (int)ft_strlen((char *)s);
	index = 0;
	i = 0;
	while (i < length)
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			index++;
		}
		i++;
	}
	return (index);
}

/*
allocating the word passed using teh given indices
*/
static char	*allocate_word(const char *s, int index, int word_length)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((word_length + 1) * sizeof(char));
	if (!word)
		return (0);
	while (i < word_length)
		word[i++] = s[index++];
	word[i] = '\0';
	return (word);
}

/*
first allocates space for the whole array of strings, it then allocates per
word according to how often it sees a continuous word. finally it sets the
last index of the array of strings to "\0"
*/
char	**ft_split(char const *s, char c)
{
	int		i;
	int		index;
	char	**new;
	int		word_length;

	if (!s)
		return (0);
	i = 0;
	new = ft_calloc((calc_size(s, c) + 1), sizeof(char *));
	if (!new)
		return (0);
	index = 0;
	while (index < (int)ft_strlen((char *)s))
	{
		word_length = 0;
		if (s[index] != c)
		{
			while (s[index + word_length] && s[index + word_length] != c)
				word_length++;
			new[i++] = allocate_word(s, index, word_length);
			index += word_length;
		}
		index++;
	}
	return (new);
}
