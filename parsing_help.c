/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:42:26 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/19 08:43:53 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	init_pipes(t_minishell *com_st)
{
	int	i;

	i = 0;
	com_st->pipes = malloc(com_st->n_com * sizeof(int *));
	com_st->pids = malloc(com_st->n_com * sizeof(int));
	while (i < com_st->n_com)
	{
		com_st->pipes[i] = malloc(2 * sizeof(int));
		if (pipe(com_st->pipes[i]) == -1)
			printf("PIPE ERROR!!!");
		i++;
	}
}

void	close_and_free2(t_minishell *com_st, t_node *cur, int *j)
{
	close_pipes(com_st);
	free(cur->unparsed);
	free(cur);
	free_command(&com_st);
	*j = 1;
}

void	main_proc(t_minishell *com_st, char **temp)
{
	t_node		*cur;
	int			i[2];

	i[1] = 0;
	i[0] = 0;
	cur = com_st->commands;
	cur = ft_lstnew();
	while (cur && temp[i[0]] && !i[1])
	{
		if (i[0] != 0)
			cur = ft_lstnew();
		cur->unparsed = temp[i[0]++];
		spacings(com_st, cur);
		if (check_dollar_exp(cur))
		{
			dollar_exp(com_st, cur);
			redirection(cur);
			ft_lstadd_back(&com_st->commands, cur);
		}
		else
			close_and_free2(com_st, cur, &i[1]);
	}
	ft_free(temp);
	if (!i[1])
		execution(com_st);
}

void	free_pipes(t_minishell *com_st)
{
	int	i;

	if (com_st->pipes)
	{
		i = 0;
		while (i < com_st->n_com)
			free(com_st->pipes[i++]);
		free(com_st->pipes);
	}
	if (com_st->pids)
		free(com_st->pids);
}

void	split_parse(char *input, t_minishell *com_st)
{
	char	**temp;

	if (syntax_error(input) == 0)
	{
		temp = ref_split(input, '|');
		com_st->n_com = count_args(temp);
		init_pipes(com_st);
		if (temp && temp[0])
			main_proc(com_st, temp);
		else if (temp)
		{
			g_exitcode = 0;
			ft_free(temp);
			free_pipes(com_st);
		}
	}
	else
		g_exitcode = 2;
	if (input)
		free (input);
}
