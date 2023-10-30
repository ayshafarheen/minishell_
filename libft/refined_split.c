/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refined_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:27:48 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/18 14:04:31 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	assign_quote(char quote_type, char letter)
{
	if ((letter == '\'' || letter == '\"') && !quote_type)
		quote_type = letter;
	else if (quote_type == letter)
		quote_type = 0;
	return (quote_type);
}

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

static int	calc_size_ref(const char *s, char c)
{
	int		i;
	int		index;
	int		length;
	char	quote_type;

	quote_type = 0;
	length = (int)ft_strlen((char *)s);
	index = 0;
	i = 0;
	while (i < length)
	{
		quote_type = assign_quote(quote_type, s[i]);
		if (s[i] != c || quote_type)
		{
			while (s[i] && (s[i] != c || quote_type))
				quote_type = assign_quote(quote_type, s[++i]);
			index++;
		}
		i++;
	}
	return (index);
}

/*
first allocates space for the whole array of strings, it then allocates per
word according to how often it sees a continuous word. finally it sets the
last index of the array of strings to "\0"
*/
char	**ref_split(char const *s, char c)
{
	int		i[3];
	char	**new;
	char	qtype;

	qtype = 0;
	if (!s)
		return (0);
	i[0] = 0;
	new = ft_calloc((calc_size_ref(s, c) + 1), sizeof(char *));
	if (!new)
		return (0);
	i[1] = -1;
	while (++i[1] < (int)ft_strlen((char *)s))
	{
		i[2] = -1;
		if (s[i[1]] != c)
		{
			while (s[i[1] + (++(i[2]))] && (s[i[1] + i[2]] != c || qtype))
				qtype = assign_quote(qtype, s[i[1] + i[2]]);
			new[i[0]++] = allocate_word(s, i[1], i[2]);
			i[1] += i[2];
		}
	}
	return (new);
}
