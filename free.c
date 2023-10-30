/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:59:41 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/18 03:23:03 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	req_free(t_minishell *com_struct, int exitc)
{
	free_command(&com_struct);
	free_all(&com_struct, -1);
	if (exitc != -1)
	{
		g_exitcode = exitc;
		exit(g_exitcode);
	}
}

void	ft_free(char **mat)
{
	int	i;

	i = 0;
	if (mat)
	{
		while (mat[i])
			free(mat[i++]);
		free(mat);
		mat = NULL;
	}
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		free2(env->val, NULL, env->var);
		env = env->next;
		free(temp);
	}
}

void	free_all(t_minishell **com_struct, int flag)
{
	if ((*com_struct))
	{
		if (flag < 0)
		{
			free_env((*com_struct)->env);
			free_env((*com_struct)->expo);
			ft_free((*com_struct)->envir);
			free((*com_struct));
			(*com_struct) = NULL;
		}
	}
}

void	free_command(t_minishell **com_struct)
{
	t_node	*val;
	t_node	*temp;

	val = (*com_struct)->commands;
	while (val)
	{
		ft_free(val->args);
		ft_free(val->iofiles);
		free2(val->unparsed, val->oi_opentype, NULL);
		temp = val;
		val = val->next;
		free(temp);
	}
	(*com_struct)->commands = NULL;
	free_pipes(*com_struct);
}
