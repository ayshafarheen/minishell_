/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:22:32 by nalshebl          #+#    #+#             */
/*   Updated: 2023/08/18 13:54:10 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	free2(char *str, int *in, char *str2)
{
	if (str)
		free(str);
	if (in)
		free (in);
	if (str2)
		free (str2);
}

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*cur_node;

	if (!(*lst))
		*lst = new;
	else
	{
		cur_node = *lst;
		while (cur_node -> next)
			cur_node = cur_node -> next;
		cur_node -> next = new;
	}
}

int	isnum(char a)
{
	if (a >= '0' && a <= '9')
		return (1);
	return (0);
}

int	alpha(char a)
{
	if ((a >= 'A' && a <= 'Z' ) || (a >= 'a' && a <= 'z') || a == '_')
		return (1);
	return (0);
}

void	print_linkedlst(t_minishell *com_struct)
{
	t_node	*cur;

	cur = com_struct->commands;
	while (cur)
	{
		printf("%s\n", cur->unparsed);
		cur = cur->next;
	}
}
