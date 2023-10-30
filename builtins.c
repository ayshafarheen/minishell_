/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:01:53 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/19 15:38:05 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	ft_ncheck(char *word)
{
	int	i;

	i = 1;
	if (word[0] && word[0] == '-')
	{
		while (word[i] && word[i] == 'n')
			i++;
		if (i == 1 || (word[i] && word[i] != 'n'))
			return (0);
	}
	else
		return (0);
	return (1);
}

int	exec_echo(t_node *cur)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (cur->args)
	{
		while (cur->args[i] && ft_ncheck(cur->args[i]))
		{
			flag += 1;
			i++;
		}
		i = 1 + flag;
		while (cur->args[i] && cur->args[i + 1])
			ft_printf("%s ", cur->args[i++]);
		if (cur->args[i])
			ft_printf("%s", cur->args[i]);
		if (!flag)
			ft_printf("\n");
		if (cur->outfd != -1 && cur->outfd != 0)
			close(cur->outfd);
	}
	return (1);
}

void	imp_unset(char *var, t_env **lst)
{
	t_env	*cur;
	t_env	*temp;

	if (ft_strcmp((*lst)->var, var) == 0)
	{
		free((*lst)->var);
		free((*lst)->val);
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
		return ;
	}
	cur = *lst;
	while (cur && cur->next)
	{
		if (ft_strcmp(cur->next->var, var) == 0)
		{
			free(cur->next->var);
			free(cur->next->val);
			temp = cur->next;
			cur->next = cur->next->next;
			free(temp);
		}
		cur = cur->next;
	}
}

int	exec_unset(t_node *cur, t_minishell *com_struct)
{
	int	i;

	i = 1;
	if (export_validation(cur) == 1)
	{
		while (cur->args[i])
		{
			imp_unset(cur->args[i], &com_struct->expo);
			imp_unset(cur->args[i], &com_struct->env);
			i++;
		}
	}
	return (1);
}

void	close_and_free(int in, int out, t_minishell *com_struct, int num)
{
	if (in != -1 && out != -1)
	{
		close(in);
		close(out);
	}
	close_pipes(com_struct);
	req_free(com_struct, num);
}
