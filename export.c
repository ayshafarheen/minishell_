/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:10:11 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/18 13:53:21 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	add_to_env(char *loc, t_env *cur, char *check, t_minishell *com_struct)
{
	if (loc && cur->val == NULL)
		ft_lstadd_backenv(&com_struct->env, ft_lstnewenv(check));
	free(check);
	if (loc)
	{
		free(cur->val);
		cur->val = ft_strdup((const char *)loc + 1);
		set_env(cur->var, loc + 1, com_struct->env);
	}
}

int	case_existance(t_minishell *com_struct, char *var)
{
	t_env	*cur;
	char	*check;
	char	*loc;

	cur = com_struct->expo;
	loc = ft_strchr(var, '=');
	if (loc)
		check = ft_strndup((const char *)var, loc - var);
	else
		check = ft_strdup((const char *)var);
	while (cur && check)
	{
		if (cur->var && ft_strcmp(check, cur->var) == 0)
		{
			add_to_env(loc, cur, check, com_struct);
			return (1);
		}
		cur = cur->next;
	}
	free(check);
	return (0);
}

void	case_notexist(t_minishell *com_struct, char *var)
{
	ft_lstinsert(&com_struct->expo, ft_lstnewenv(var));
	if (ft_strchr(var, '='))
		ft_lstadd_backenv(&com_struct->env, ft_lstnewenv(var));
}

int	export_validation(t_node *cur)
{
	int	i;

	i = 1;
	while (cur->args[i])
	{
		if (!alpha(cur->args[i][0]) || ft_isalnum(cur->args[i]) == 0)
		{
			write_error(cur->args[0], cur->args[i],
				"not a valid identifier", -1);
			g_exitcode = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	exec_export(t_node *cur, t_minishell *com_struct)
{
	int	i;

	if (export_validation(cur) == 1)
	{
		if (!cur->args[1])
			print_export(com_struct);
		else
		{
			i = 1;
			while (cur->args[i])
			{
				if (!case_existance(com_struct, cur->args[i]))
					case_notexist(com_struct, cur->args[i]);
				i++;
			}
		}
	}
	return (1);
}
