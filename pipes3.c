/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:13:20 by nalshebl          #+#    #+#             */
/*   Updated: 2023/08/31 08:35:11 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	wait_and_free(t_minishell *com_struct, int loop)
{
	int	i;
	int	x;

	i = 0;
	i = 0;
	close_pipes(com_struct);
	while (i < com_struct->n_com && loop != 1)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(com_struct->pids[i++], &x, 0);
	}
	if (loop != 1 && WIFSIGNALED(x))
		g_exitcode = 128 + x;
	else if (loop != 1)
		g_exitcode = WEXITSTATUS(x);
	free_command(&com_struct);
	unlink("h_d_file");
}

void	close_fds(t_node *cur)
{
	if (cur->outfd != -1 && cur->outfd != 0)
		close (cur->outfd);
	if (cur->infd != -1 && cur->infd != 0)
		close (cur->infd);
}

void	infile_fail(t_node *cur, t_minishell *com_struct, int i)
{
	close_fds(cur);
	com_struct->pids[i] = basic_error(com_struct, -1,
			"fork error!\n", fork());
	if (com_struct->pids[i] == 0)
	{
		close_pipes(com_struct);
		req_free(com_struct, g_exitcode);
	}
}

void	exec_nofail(t_minishell *com_struct, t_node *cur, int i)
{
	com_struct->pids[i] = basic_error(com_struct, -1,
			"fork error!\n", fork());
	if (com_struct->pids[i] == 0)
	{
		exec_command(cur, com_struct, i, 0);
		req_free(com_struct, g_exitcode);
	}
}
