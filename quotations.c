/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:23:17 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/16 10:35:35 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	det_quote(t_node *cur, char *quote_type, int i, int *file)
{
	int	flag;

	flag = 1;
	if (cur->unparsed[i] == '\'' && !(*quote_type))
		(*quote_type) = '\'';
	else if (cur->unparsed[i] == '\"' && !(*quote_type))
		(*quote_type) = '\"';
	else if ((*quote_type) == cur->unparsed[i])
	{
		(*quote_type) = 0;
		if (file)
			*file = 0;
	}
	else
		flag = 0;
	return (flag);
}

void	quotations(t_node *cur)
{
	char	q_type;
	int		i;
	int		k;
	char	*final;

	i = -1;
	k = 0;
	q_type = 0;
	final = NULL;
	if (cur->unparsed)
	{
		final = ft_calloc(ft_strlen(cur-> unparsed) + 1, sizeof(char));
		if (!final)
			return ;
		while (cur->unparsed[++i])
			if (!det_quote(cur, &q_type, i, NULL) && cur->unparsed[i] != q_type)
				final[k++] = cur->unparsed[i];
		free(cur->unparsed);
	}
	cur->unparsed = final;
}

void	case_quotes_bracs(char **final, t_node *cur, int *i, int *j)
{
	char	quote_type;

	quote_type = 0;
	if ((cur->unparsed[(*i)] == '\'' || cur->unparsed[(*i)] == '\"'))
	{
		(*final)[(*j)++] = cur->unparsed[*i];
		quote_type = cur->unparsed[(*i)++];
		while (cur->unparsed[(*i)] && cur->unparsed[(*i)] != quote_type)
			(*final)[(*j)++] = cur->unparsed[(*i)++];
		(*final)[(*j)++] = cur->unparsed[(*i)];
		quote_type = 0;
	}
	else if (cur->unparsed[(*i)] == '<' || cur->unparsed[(*i)] == '>')
	{
		if ((*j) > 0 && (*final)[(*j) - 1] != ' ')
			(*final)[(*j)++] = ' ';
		(*final)[(*j)++] = cur->unparsed[(*i)++];
		while (cur->unparsed[(*i)]
			&& cur->unparsed[(*i) - 1] == cur->unparsed[(*i)])
			(*final)[(*j)++] = cur->unparsed[(*i)++];
		if (cur->unparsed[(*i)] && cur->unparsed[(*i)] != ' ')
			(*final)[(*j)++] = ' ';
		(*i)--;
	}
}
