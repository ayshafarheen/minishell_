/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:12:28 by nalshebl          #+#    #+#             */
/*   Updated: 2023/08/19 15:55:57 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	open_all(t_node *cur, t_minishell *com_struct, int flag)
{
	int		i;
	int		fd[2];

	i = -1;
	fd[0] = 0;
	fd[1] = 0;
	cur->infd = -1;
	cur->outfd = -1;
	while (cur->iofiles && cur->iofiles[++i] && !com_struct->c)
	{
		det_fd(&fd[0], &fd[1], cur, (int []){flag, i, com_struct->n_com});
		if (cur->oi_opentype[i] == 4 || cur->oi_opentype[i] == 3)
		{
			if (case_outfiles(cur, i, fd[1]) == -2)
				return (-2);
		}
		else
		{
			if (cur->oi_opentype[i] == 2 && g_exitcode == 1)
				com_struct->c = 1;
			if (case_infiles(cur, i, fd[0]) == -2)
				return (-2);
		}
	}
	return (0);
}

void	close_pipes(t_minishell *com_struct)
{
	int	j;

	j = 0;
	while (j < com_struct->n_com)
	{
		close(com_struct->pipes[j][0]);
		close(com_struct->pipes[j][1]);
		j++;
	}
}

void	dup_req(t_node *cur, t_minishell *com_struct, int i)
{
	if (cur->infd != -1 && cur->infd != 0)
	{
		basic_error(com_struct, cur->infd,
			"dup error\n", dup2(cur->infd, STDIN_FILENO));
		close(cur->infd);
	}
	else if (i != 0)
		basic_error(com_struct, com_struct->pipes[i][0],
			"dup error\n", dup2(com_struct->pipes[i][0], STDIN_FILENO));
	if (cur->outfd != -1)
	{
		basic_error(com_struct, cur->outfd,
			"dup error\n", dup2(cur->outfd, STDOUT_FILENO));
		close(cur->outfd);
	}
}

void	exec_command(t_node *cur, t_minishell *com_st, int i, int flag)
{
	dup_req(cur, com_st, i);
	if (i + 1 < com_st->n_com && cur->outfd == -1)
		basic_error(com_st, com_st->pipes[i + 1][1],
			"dup error!\n", dup2(com_st->pipes[i + 1][1], STDOUT_FILENO));
	close_pipes(com_st);
	if (cur->args && !check_builtin(cur, com_st, -1, -1) && !flag)
	{
		if (!ft_strchr(cur->args[0], '/') || access(cur->args[0], X_OK) != 0)
			cur->args[0] = parse_path(cur->args[0], &com_st);
		g_exitcode = write_error(cur->args[0], cur->args[1],
				"exec error", execve(cur->args[0], cur->args, com_st->envir));
		req_free(com_st, g_exitcode);
	}
}

int	single_command(t_minishell *com_st)
{
	int		in;
	int		out;
	t_node	*cur;
	int		returnval;

	returnval = 0;
	cur = com_st->commands;
	if (com_st->n_com == 1)
	{
		if (open_all(cur, com_st, 0) != -2)
		{
			in = basic_error(com_st, -1, "dup error!\n", dup(STDIN_FILENO));
			out = basic_error(com_st, -1, "dup error!\n", dup(STDOUT_FILENO));
			dup_req(cur, com_st, 0);
			if (check_builtin(cur, com_st, in, out) || !(cur->args))
				returnval = 1;
			basic_error(com_st, in, "dup error!\n", dup2(in, STDIN_FILENO));
			close(in);
			basic_error(com_st, out, "dup error!\n", dup2(out, STDOUT_FILENO));
			close(out);
		}
		else
			returnval = 1;
	}
	return (returnval);
}
