/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 02:37:46 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/19 15:54:34 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*rl_fn(t_minishell *com_st)
{
	char	*input;

	input = readline("my minishell ");
	if (input == NULL)
	{
		free_all(&com_st, -1);
		printf("exit\n");
		exit(0);
	}
	return (input);
}

int	basic_error(t_minishell *com_struct, int fd, char *msg, int val)
{
	if (val < 0)
	{
		if (fd)
			close(fd);
		write(2, msg, ft_strlen(msg));
		req_free(com_struct, 1);
	}
	return (val);
}

void	convert_to_2d(t_minishell **com_struct)
{
	t_env	*env;
	char	*var;
	int		i;
	char	*temp;

	i = -1;
	env = (*com_struct)->env;
	while (env && env->var && ++i > -1)
		env = env->next;
	(*com_struct)->envir = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	env = (*com_struct)->env;
	while (env && env->var)
	{
		var = ft_strjoin(env->var, "=");
		if (env->val)
		{
			temp = var;
			var = ft_strjoin(var, env->val);
			free(temp);
		}
		(*com_struct)->envir[i++] = var;
		env = env->next;
	}
}

t_node	*closeunlink(t_node *cur, t_minishell **com_struct)
{
	close_fds(cur);
	ft_free((*com_struct)->envir);
	(*com_struct)->envir = NULL;
	cur = cur->next;
	unlink("h_d_file");
	return (cur);
}

void	execution(t_minishell *com_struct)
{
	int		i;
	int		loop;
	t_node	*cur;

	cur = com_struct->commands;
	i = -1;
	com_struct->c = 0;
	signal(SIGQUIT, &handler);
	loop = single_command(com_struct);
	while (++i < com_struct->n_com && cur != 0 && loop != 1)
	{
		g_exitcode = 0;
		convert_to_2d(&com_struct);
		if (!com_struct->c && open_all(cur, com_struct, 1) != -2)
		{
			if (!com_struct->c)
				exec_nofail(com_struct, cur, i);
			else
				infile_fail(cur, com_struct, i);
		}
		else
			infile_fail(cur, com_struct, i);
		cur = closeunlink(cur, &com_struct);
	}
	wait_and_free(com_struct, loop);
}
