/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:26:22 by nalshebl          #+#    #+#             */
/*   Updated: 2023/08/19 14:43:32 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	isnumber(char *num)
{
	int	i;

	i = 0;
	if (num[0] && (num[0] == '-' || num[0] == '+'))
		i++;
	while (num[i])
	{
		if (num[i] >= '0' && num[i] <= '9')
			i++;
		else
			return (0);
		g_exitcode = ft_atoi(num);
		if (((g_exitcode == -1 && ft_strlen(num) > 2)
				|| (g_exitcode == 0 && ft_strlen(num) > 1))
			&& ft_strcmp("9223372036854775807", num) != 0
			&& ft_strcmp("-9223372036854775807", num) != 0
			&& ft_strcmp("-9223372036854775808", num) != 0)
			return (0);
		return (1);
	}
	return (0);
}

void	error_exit(t_minishell *com_struct, t_node *cur, int in, int out)
{
	if (isnumber(cur->args[1]) == 0)
	{
		write_error(cur->args[0], cur->args[1],
			"numeric argument required", -1);
		close_and_free(in, out, com_struct, 255);
	}
	if (g_exitcode < 0)
		g_exitcode = 256 - (-g_exitcode);
	close_and_free(in, out, com_struct, g_exitcode);
}

int	exec_exit(t_node *cur, t_minishell *com_struct, int in, int out)
{
	if (com_struct->n_com == 1)
		ft_printf("exit\n");
	if (cur && cur->args && cur->args[1])
	{
		if (cur->args[2] && isnumber(cur->args[1]))
		{
			write_error(cur->args[0], NULL, "too many arguments", -1);
			g_exitcode = 1;
		}
		else
			error_exit(com_struct, cur, in, out);
	}
	else
		close_and_free(in, out, com_struct, g_exitcode);
	return (1);
}

void	complete_cd(t_minishell *com_struct, char *dir)
{
	char	*newval;

	newval = ft_strjoin("OLDPWD=", dir);
	case_existance(com_struct, newval);
	free(newval);
	free(dir);
	dir = getcwd(NULL, 0);
	set_env("PWD", dir, com_struct->expo);
	set_env("PWD", dir, com_struct->env);
	free(dir);
}

int	exec_cd(t_node *cur, t_minishell *com_struct)
{
	int		error;
	char	*dir;

	error = 0;
	if (cur->args[1])
	{
		dir = getcwd(NULL, 0);
		error = chdir(cur->args[1]);
		error = write_error(cur->args[0], NULL, strerror(errno), error);
		if (error)
		{
			free(dir);
			g_exitcode = 1;
		}
		else
			complete_cd(com_struct, dir);
	}
	else
	{
		write_error(cur->args[0], NULL, "Incorrect number of arguments", -1);
		g_exitcode = 1;
	}
	return (1);
}
