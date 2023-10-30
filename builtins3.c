/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:27:35 by nalshebl          #+#    #+#             */
/*   Updated: 2023/08/17 14:26:58 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	exec_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	ft_printf("%s\n", dir);
	free(dir);
	return (1);
}

int	check_builtin(t_node *cur, t_minishell *com_struct, int in, int out)
{
	if (cur->args && (ft_strcmp(cur->args[0], "/bin/echo") == 0
			|| (ft_strcmp(cur->args[0], "echo") == 0)))
		return (exec_echo(cur));
	else if (cur->args && (ft_strcmp(cur->args[0], "/usr/bin/cd") == 0
			|| (ft_strcmp(cur->args[0], "cd") == 0)))
		return (exec_cd(cur, com_struct));
	else if (cur->args && (ft_strcmp(cur->args[0], "/bin/pwd") == 0
			|| (ft_strcmp(cur->args[0], "pwd") == 0)))
		return (exec_pwd());
	else if (cur->args && ft_strcmp(cur->args[0], "export") == 0)
		return (exec_export(cur, com_struct));
	else if (cur->args && (ft_strcmp(cur->args[0], "/usr/bin/env") == 0
			|| (ft_strcmp(cur->args[0], "env") == 0)))
		return (print_env(com_struct));
	else if (cur->args && ft_strcmp(cur->args[0], "unset") == 0)
		return (exec_unset(cur, com_struct));
	else if (cur->args && ft_strcmp(cur->args[0], "exit") == 0)
		return (exec_exit(cur, com_struct, in, out));
	return (0);
}

char	*find_not_alnum(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] >= 'a' && word[i] <= 'z')
			i++;
		else if (word[i] >= 'A' && word[i] <= 'Z')
			i++;
		else if (word[i] >= '0' && word[i] <= '9')
			i++;
		else
			return (&word[i]);
	}
	return (&word[i]);
}

int	check_dollar_exp(t_node *cur)
{
	char	q_type;
	int		i;
	int		j;

	i = -1;
	j = 0;
	q_type = 0;
	if (cur->unparsed)
	{
		while (cur->unparsed[++i])
		{
			cur->flag = 0;
			if (!det_quote(cur, &q_type, i, &(cur->file))
				&& (cur->unparsed[i + 1]
					&& cur->unparsed[i] == '$' && (cur->unparsed[i + 1] == '\''
						|| cur->unparsed[i + 1] == '\"')) && !q_type)
				cur->flag = 1;
			if (cur->flag)
				cur->expansion_opt[j++] = 's';
			set_exp(cur, q_type, &i, &j);
		}
	}
	if (q_type)
		return (write_error(NULL, NULL, "Error: Unclosed quotes", -1), 0);
	return (1);
}

void	print_export(t_minishell *com_struct)
{
	t_env	*cur;

	cur = com_struct->expo;
	while (cur)
	{
		if (cur->val && cur->var)
			ft_printf("declare -x %s=\"%s\"\n", cur->var, cur->val);
		else
			ft_printf("declare -x %s\n", cur->var);
		cur = cur->next;
	}
}
