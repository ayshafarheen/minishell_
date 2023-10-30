/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:44:57 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/19 08:41:40 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*no_exp(char *final, char *to_be_added, char *start)
{
	char	*temp;

	temp = final;
	final = ft_strjoin(final, to_be_added);
	free(temp);
	free(to_be_added);
	to_be_added = copy_till_end_single(start);
	temp = final;
	final = ft_strjoin(final, to_be_added);
	free(temp);
	temp = NULL;
	free(to_be_added);
	return (final);
}

char	*req_exp(t_minishell *com_struct, char *t_b_a, char *final, char o)
{
	char	*temp;
	char	*check;

	temp = NULL;
	check = get_myenv(com_struct, t_b_a + 1);
	if (check && o != 'h')
	{
		temp = final;
		final = ft_strjoin(final, check);
		if (*(t_b_a + 1) == '?')
			free(check);
	}
	else if (!t_b_a[1] || o == 'f' || o == 'h')
	{
		temp = final;
		final = ft_strjoin(final, t_b_a);
	}
	if (temp)
		free(temp);
	free(t_b_a);
	return (final);
}

char	*calc_new_pos(char *start)
{
	char	*temp2;

	temp2 = NULL;
	if (start[0] && start[0] == '$' && start[1] && start[1] == '?')
		temp2 = start + 2;
	else if (ft_isalnum2(start + 1) == 0)
		temp2 = find_not_alnum(start + 1);
	if (temp2)
		start = temp2;
	else
		start += ft_strlen(start);
	return (start);
}

char	*find_next_exapnsion(char *start, char *final)
{
	char	*to_be_added;
	char	*temp;

	to_be_added = copy_till(start, '$');
	temp = final;
	final = ft_strjoin(final, to_be_added);
	free(temp);
	free(to_be_added);
	return (final);
}

void	dollar_exp(t_minishell *com_struct, t_node *cur)
{
	char	*start;
	char	*final;
	char	*t_b_a;
	int		j;

	final = till_first_exp(cur);
	start = ft_strchr(cur->unparsed, '$');
	j = 0;
	while (start && *start)
	{
		t_b_a = copy_till_end(start, cur->expansion_opt[j]);
		if (cur->expansion_opt[j] == '\"' || cur->expansion_opt[j] == 'f')
			final = req_exp(com_struct, t_b_a, final, cur->expansion_opt[j]);
		else
			final = no_exp(final, t_b_a, start);
		start = calc_new_pos(start);
		final = find_next_exapnsion(start, final);
		if (start && *start && *start != '$')
			start = ft_strchr(start, '$');
		j++;
	}
	if (cur->unparsed)
		free(cur->unparsed);
	cur->unparsed = final;
}
