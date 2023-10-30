/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:03:56 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/19 16:00:00 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	here_handler(int num)
{
	if (num == SIGINT)
	{
		write(2, "\nPlease press enter\n", 20);
		rl_on_new_line ();
		rl_replace_line("", 0);
		g_exitcode = 1;
	}
}

void	hd_input(char *file, int fd)
{
	char	*temp;

	temp = get_next_line(0);
	while (temp)
	{
		if (g_exitcode == 1)
			break ;
		if (ft_strcmp(file, temp) != 0 && fd != -1)
		{
			write(fd, temp, ft_strlen(temp));
			free(temp);
			temp = get_next_line(0);
		}
		else
			break ;
	}
	free(temp);
}

int	heredoc(char *filename)
{
	char	*file;
	int		fd;

	fd = 0;
	g_exitcode = 0;
	signal(SIGINT, &here_handler);
	signal(SIGQUIT, SIG_IGN);
	fd = open("h_d_file", O_TRUNC | O_WRONLY | O_CREAT, 0666);
	file = ft_strjoin(filename, "\n");
	hd_input(file, fd);
	free(file);
	close(fd);
	fd = open("h_d_file", O_RDONLY);
	return (fd);
}

void	det_fd(int *fdi, int *fdo, t_node *cur, int *vals)
{
	int	i;
	int	flag;
	int	ncom;

	flag = vals[0];
	i = vals[1];
	ncom = vals[2];
	if (cur->oi_opentype[i] == 1)
		*fdi = open((cur->iofiles)[i], O_RDONLY);
	else if (cur->oi_opentype[i] == 2 && (flag == 0
			|| ncom > 1))
		*fdi = heredoc((cur->iofiles)[i]);
	else if (cur->oi_opentype[i] == 2
		&& ncom == 1 && flag == 1)
		*fdi = open("h_d_file", O_RDONLY);
	else if (cur->oi_opentype[i] == 3)
		*fdo = open((cur->iofiles)[i], O_TRUNC | O_WRONLY | O_CREAT, 0666);
	else if (cur->oi_opentype[i] == 4)
		*fdo = open((cur->iofiles)[i], O_APPEND | O_WRONLY | O_CREAT, 0666);
}

int	case_infiles(t_node *cur, int i, int fdi)
{
	write_error(cur->iofiles[i], NULL, strerror(errno), fdi);
	if (fdi == -1)
	{
		g_exitcode = 1;
		if (cur->infd != -1 && cur->infd != 0)
			close(cur->infd);
		if (cur->outfd != -1 && cur->outfd != 0)
			close(cur->outfd);
		return (-2);
	}
	if (cur->infd != -1 && cur->infd != 0)
		close(cur->infd);
	cur->infd = fdi;
	return (0);
}
