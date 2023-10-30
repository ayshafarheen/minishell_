/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalshebl <nalshebl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:53:23 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/16 18:20:56 by nalshebl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	if_sing(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, "<<") == 0)
		return (2);
	else if (ft_strcmp(str, ">") == 0)
		return (3);
	else if (ft_strcmp(str, ">>") == 0)
		return (4);
	else
		return (0);
}

char	det_quote2(char *str, char *quote_type, int i)
{
	int	flag;

	flag = 1;
	if (str[i] == '\'' && !(*quote_type))
		(*quote_type) = '\'';
	else if (str[i] == '\"' && !(*quote_type))
		(*quote_type) = '\"';
	else if ((*quote_type) == str[i])
		(*quote_type) = 0;
	else
		flag = 0;
	return (flag);
}

char	*quotations2(char *str)
{
	char	q_type;
	int		i;
	int		k;
	char	*final;

	i = -1;
	k = 0;
	q_type = 0;
	final = NULL;
	if (str)
	{
		final = ft_calloc(ft_strlen(str) + 1, sizeof(char));
		if (!final)
			return (0);
		while (str[++i])
			if (!det_quote2(str, &q_type, i) && str[i] != q_type)
				final[k++] = str[i];
		free(str);
	}
	return (final);
}

int	is_redirection(char *str)
{
	int	res;

	res = if_sing(str);
	return ((res > 0 && res < 3) || (res > 2 && res < 5));
}

char	ft_command(char *str)
{
	if (is_redirection(str) || is_redirection(str + 1))
	{
		return (1);
	}
	printf("Command: %s\n", str);
	return (0);
}
