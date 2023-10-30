/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:01:43 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/17 19:38:53 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_node	*ft_lstnew(void)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (0);
	new->next = NULL;
	return (new);
}

t_env	*ft_lstnewenv(char *var)
{
	t_env	*new;
	char	*loc;

	new = malloc(1 * sizeof(t_env));
	if (!new)
		return (0);
	loc = ft_strchr(var, '=');
	if (loc)
	{
		new->var = ft_strndup((const char *)var, loc - var);
		new->val = ft_strdup((const char *)loc + 1);
	}
	else
	{
		new->var = ft_strdup((const char *)var);
		new->val = NULL;
	}
	new -> next = NULL;
	return (new);
}

void	ft_lstadd_backenv(t_env **lst, t_env *new)
{
	t_env	*cur_node;

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

void	find_pos(t_env *cur_node, t_env *new)
{
	t_env	*temp;

	while (cur_node->next)
	{
		if (ft_strcmp(new->var, cur_node->next->var) < 0)
		{
			temp = cur_node->next;
			cur_node->next = new;
			new->next = temp;
			return ;
		}
		cur_node = cur_node->next;
	}
	cur_node->next = new;
}

void	ft_lstinsert(t_env **lst, t_env *new)
{
	t_env	*cur_node;

	if (!(*lst))
		*lst = new;
	else
	{
		cur_node = *lst;
		if (ft_strcmp(new->var, cur_node->var) < 0)
		{
			new->next = cur_node;
			(*lst) = new;
			return ;
		}
		find_pos(cur_node, new);
	}
}
