/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:03:16 by afarheen          #+#    #+#             */
/*   Updated: 2023/09/12 09:15:24 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	printf_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			printf("\n%s\n", arr[i++]);
	}
}

void	ft_print(t_minishell *com_struct)
{
	t_node	*cur;

	cur = com_struct->commands;
	while (cur)
	{
		printf_arr(cur->infile);
		printf_arr(cur->args);
		printf_arr(cur->outfile);
		cur = cur->next;
	}
}

void	write_stderr(char *msg, char *msg2, int flag)
{
	if (msg)
		write (2, msg, ft_strlen(msg));
	if (msg && msg2)
		write (2, ": ", 2);
	if (msg2)
		write (2, msg2, ft_strlen(msg2));
	if (flag)
		write(2, ": ", 2);
	else
		write(2, "\n", 1);
}

void	open_dir(char *cmd, int *flag)
{
	int	fd;

	fd = open(cmd, O_DIRECTORY, 0666);
	if (fd != -1)
	{
		close(fd);
		if (ft_strchr(cmd, '/'))
		{
			write(2, "Is a directory\n", 15);
			*flag = 126;
		}
	}
	else if (ft_strchr(cmd, '/'))
	{
		write(2, "No such file or directory\n", 27);
		*flag = 127;
	}
}

int	write_error(char *cmd, char *val, char *msg, int flag)
{
	if (flag < 0)
	{
		write(2, "minishell: ", 11);
		write_stderr(cmd, val, 1);
		if (cmd)
			open_dir(cmd, &flag);
		if (msg && flag != 127 && flag != 126)
			write_stderr(msg, NULL, 0);
	}
	return (flag);
}
