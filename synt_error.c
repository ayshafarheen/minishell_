/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synt_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:40:19 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/19 08:45:58 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	check_synt_err(char *input, int *i, int *nw, char *quote_type)
{
	char	type;

	type = input[*i];
	while (input[(*i)])
	{
		(*i)++;
		if ((type == '<' || type == '>' ) && (!input[(*i)] || input[(*i)] == '<'
				|| input[(*i)] == '>' || input[(*i)] == '|'))
			return (write_error(NULL, NULL, "syntax error", -1), 1);
		else if (type == '|' && (!input[(*i)] || input[(*i)] == '|'))
			return (write_error(NULL, NULL, "syntax error", -1), 1);
		else if (type == '|' && (input[(*i)] == '<' || input[(*i)] == '>'))
			return ((*i)--, 0);
		else if (ft_isspace(input[(*i)]))
			;
		else
		{
			if (input[(*i)] == '\'' || input[(*i)] == '\"')
				*quote_type = input[(*i)];
			(*nw)++;
			break ;
		}
	}
	return (0);
}

int	syntax_error(char *input)
{
	int		i[2];
	char	quote_type;
	int		error;

	i[0] = 0;
	i[1] = 0;
	quote_type = 0;
	error = 0;
	while (input[i[0]] && error == 0)
	{
		if ((input[i[0]] == '\'' || input[i[0]] == '\"') && !quote_type)
		{
			quote_type = input[i[0]];
			i[1]++;
		}
		else if (quote_type == input[i[0]])
			quote_type = 0;
		else if (quote_type || input[i[0]] == ' ')
			;
		else
			error = syntax_err_2(input, &i[0], &i[1], &quote_type);
		if (input[i[0]])
			i[0]++;
	}
	return (error);
}

int	syntax_err_2(char *input, int *i, int *nw, char *quote_type)
{
	int	error;

	error = 0;
	if (input[(*i)] == '<' || input[(*i)] == '>')
	{
		if (input[(*i) + 1] && input[(*i)] == input[(*i) + 1])
			(*i)++;
		error = check_synt_err(input, i, nw, quote_type);
	}
	else if (input[(*i)] == '|')
	{
		if (!*nw)
			error = write_error(NULL, NULL, "syntax error", -1);
		else
			*nw = 0;
		if (error == 0)
			error = check_synt_err(input, i, nw, quote_type);
	}
	else
		(*nw)++;
	return (error);
}
