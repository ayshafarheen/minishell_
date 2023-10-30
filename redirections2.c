/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:20:36 by nalshebl          #+#    #+#             */
/*   Updated: 2023/08/19 15:59:18 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	count_in(char **temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp[i])
	{
		if (if_sing(temp[i]) == 1 || if_sing(temp[i]) == 2)
			j++;
		i++;
	}
	return (j);
}

int	count_all(char **temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp[i])
	{
		if (if_sing(temp[i]) == 3 || if_sing(temp[i]) == 4
			|| if_sing(temp[i]) == 1 || if_sing(temp[i]) == 2)
			j++;
		i++;
	}
	return (j);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	if (args)
		while (args[i])
			i++;
	return (i);
}

void	init_free_red(t_node **cur, char **temp, int flag, int *i)
{
	if (i)
	{
		(*cur)->iofiles[i[1] + 1] = NULL;
		(*cur)->args[i[2]] = NULL;
	}
	if (flag)
	{
		(*cur)->iofiles = malloc(sizeof(char *) * (count_all(temp) + 1));
		(*cur)->oi_opentype = malloc(sizeof(int) * count_all(temp));
		(*cur)->args = malloc(sizeof(char *) * (count_args(temp) + 1));
	}
	else
	{
		if (!(*cur)->iofiles[0])
		{
			ft_free((*cur)->iofiles);
			(*cur)->iofiles = NULL;
		}
		if (!(*cur)->args[0])
		{
			ft_free((*cur)->args);
			(*cur)->args = NULL;
		}
		ft_free(temp);
	}
}

void	redirection(t_node *cur)
{
	char	**temp ;
	int		i[3];
	int		res;

	i[0] = -1;
	i[1] = -1;
	i[2] = 0;
	res = 0;
	temp = ref_split(cur->unparsed, ' ');
	init_free_red(&cur, temp, 1, NULL);
	while (temp[++(i[0])])
	{
		res = if_sing(temp[i[0]]);
		if (res)
		{
			cur->iofiles[++(i[1])] = quotations2(ft_strdup(temp[i[0] + 1]));
			cur->oi_opentype[i[1]] = res;
			(i[0])++;
		}
		else
			cur->args[i[2]++] = quotations2(ft_strdup(temp[i[0]]));
		if (!temp[i[0]])
			break ;
	}
	init_free_red(&cur, temp, 0, i);
}
