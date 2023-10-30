/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalshebl <nalshebl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:58:57 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/16 22:52:32 by nalshebl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_size(t_node *cur)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (cur->unparsed[i])
	{
		if (cur->unparsed[i] == '<' || cur->unparsed[i] == '>')
			len += 2;
		i++;
	}
	return (i + len);
}

char	*apply_spacing(t_node *cur, char *final)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cur->unparsed[i])
	{
		if ((cur->unparsed[i] == '\'' || cur->unparsed[i] == '\"'))
			case_quotes_bracs(&final, cur, &i, &j);
		else if (j > 0 && ft_isspace(cur->unparsed[i])
			&& ft_isspace(final[j - 1]))
			;
		else if (cur->unparsed[i] == '<' || cur->unparsed[i] == '>')
			case_quotes_bracs(&final, cur, &i, &j);
		else if (ft_isspace(cur->unparsed[i]))
			final[j++] = ' ';
		else
			final[j++] = cur->unparsed[i];
		if (cur->unparsed[i])
			i++;
	}
	return (final);
}

void	spacings(t_minishell *com_struct, t_node *cur)
{
	char	*final;

	(void)com_struct;
	if (cur->unparsed)
	{
		final = ft_calloc(calc_size(cur) + 1, sizeof(char));
		if (!final)
			return ;
		final = apply_spacing(cur, final);
		cur->unparsed = final;
	}
}
