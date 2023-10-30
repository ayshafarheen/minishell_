/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:02:49 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/17 17:59:40 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*create_path(char *arg1, char **final)
{
	char	*path2;
	char	*paths;
	int		i;

	i = 0;
	if (ft_strcmp(arg1, ".") == 0 || (ft_strcmp(arg1, "..")) == 0)
		return (0);
	while (final && final[i])
	{
		path2 = ft_strjoin(final[i], "/");
		paths = ft_strjoin(path2, arg1);
		free(path2);
		if (access(paths, X_OK) == 0)
			return (paths);
		free(paths);
		i++;
	}
	return (0);
}

void	parse_pth2(char *args, t_minishell **com_struct)
{
	write_error(args, NULL, "command not found", -1);
	close_pipes(*com_struct);
	req_free(*com_struct, 127);
}

char	*parse_path(char *args, t_minishell **com_struct)
{
	char	*paths;
	char	**final;
	char	*path;

	path = get_myenv(*com_struct, "PATH");
	if (!path)
		parse_pth2(args, com_struct);
	final = ft_split(path, ':');
	if (ft_strcmp(args, "") == 0)
	{
		ft_free(final);
		parse_pth2(args, com_struct);
	}
	paths = create_path(args, final);
	if (!paths)
	{
		ft_free(final);
		parse_pth2(args, com_struct);
	}
	ft_free(final);
	free(args);
	return (paths);
}
