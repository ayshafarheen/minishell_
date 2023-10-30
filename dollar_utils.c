/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:48:45 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/19 08:40:14 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_till(char *start, char final)
{
	int		i;
	char	*return_val;

	i = 0;
	if (!start)
		return (0);
	while (start[i])
	{
		if (start[i] == final)
		{
			return_val = ft_strndup(start, i);
			return (return_val);
		}
		i++;
	}
	return_val = ft_strdup(start);
	return (return_val);
}

char	*copy_till_end(char *start, char o)
{
	int		i;
	char	*return_val;

	i = 0;
	while (start[i] && start[i] != 0)
	{
		if (start[0] && start[1] && start[0] == '$' && start[1] == '?')
		{
			return_val = ft_strndup(start, 2);
			return (return_val);
		}
		else if (i != 0 && ft_charisalnum(start[i]) == 0)
		{
			if (o == 's')
				return_val = ft_strndup(start, i - 1);
			else
				return_val = ft_strndup(start, i);
			return (return_val);
		}
		i++;
	}
	return_val = ft_strdup(start);
	return (return_val);
}

char	*copy_till_end_single(char *start)
{
	int		i;
	char	*return_val;

	i = 0;
	while (start[i] && start[i] != 0)
	{
		if (start[0] && start[1] && start[0] == '$' && start[1] == '?')
		{
			return_val = ft_strdup("");
			return (return_val);
		}
		if (start[i] == ' ' || start[i] == '$')
		{
			return_val = ft_strndup(start, i);
			return (return_val);
		}
		i++;
	}
	return_val = ft_strdup(start);
	return (return_val);
}

char	*till_first_exp( t_node *cur)
{
	char	*final;
	char	*to_be_added;
	char	*temp;

	final = ft_strdup("");
	to_be_added = copy_till(cur->unparsed, '$');
	temp = final;
	final = ft_strjoin(final, to_be_added);
	free(temp);
	free(to_be_added);
	to_be_added = NULL;
	return (final);
}

void	set_exp(t_node *cur, char q_type, int *i, int *j)
{
	if (cur->file && cur->unparsed[(*i)] == ' ' && !q_type)
		cur->file = 0;
	if (!(cur->flag) && (cur->unparsed[(*i)] == '<'
			|| cur->unparsed[(*i)] == '>') && !q_type)
	{
		cur->file = 1;
		if (cur->unparsed[(*i) + 1] && cur->unparsed[(*i) + 1] == '<')
			cur->hd = 1;
		if (cur->unparsed[(*i) + 1] && cur->unparsed[(*i) + 1] == ' ')
			(*i)++;
	}
	else if (cur->file && cur->unparsed[(*i)] == '$'
		&& !cur->hd && q_type != '\'')
		cur->expansion_opt[(*j)++] = 'f';
	else if (cur->file && cur->unparsed[(*i)] == '$' && cur->hd)
	{
		cur->expansion_opt[(*j)++] = 'h';
		cur->hd = 0;
	}
	else if (!(cur->flag) && cur->unparsed[(*i)] == '$' && q_type)
		cur->expansion_opt[(*j)++] = q_type;
	else if (!(cur->flag) && cur->unparsed[(*i)] == '$'
		&& !q_type && !(cur->file))
		cur->expansion_opt[(*j)++] = '\"';
}
