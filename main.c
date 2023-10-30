/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:57:13 by noufalshibl       #+#    #+#             */
/*   Updated: 2023/08/19 16:00:17 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	case_outfiles(t_node *cur, int i, int fdo)
{
	write_error(cur->iofiles[i], NULL, strerror(errno), fdo);
	if (fdo == -1)
	{
		g_exitcode = 1;
		if (cur->infd != -1 && cur->infd != 0)
			close(cur->infd);
		if (cur->outfd != -1 && cur->outfd != 0)
			close(cur->outfd);
		return (-2);
	}
	if (cur->outfd != -1 && cur->outfd != 0)
		close(cur->outfd);
	cur->outfd = fdo;
	return (0);
}

void	handler(int num)
{
	if (num == SIGINT)
	{
		printf("\n");
		rl_on_new_line ();
		rl_replace_line("", 0);
		g_exitcode = 1;
		rl_redisplay();
	}
	else
	{
		rl_on_new_line ();
		rl_replace_line("", 0);
		if (num == SIGQUIT)
			write(2, "Quit: 3\n", 8);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_minishell	*com_st;

	(void) argv;
	if (argc == 1)
	{
		com_st = ft_calloc(1, sizeof(t_minishell));
		if (!com_st)
			return (0);
		create_env(com_st, envp);
		while (1)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, &handler);
			input = rl_fn(com_st);
			add_history(input);
			split_parse(input, com_st);
		}
		req_free(com_st, -1);
	}
	return (0);
}
