/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 08:54:31 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/19 14:35:49 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	set_env(char *loc, char *var, t_env *envtype)
{
	t_env	*cur;

	cur = envtype;
	while (cur)
	{
		if (ft_strcmp(loc, cur->var) == 0)
		{
			free(cur->val);
			cur->val = ft_strdup((const char *)var);
			return ;
		}
		cur = cur->next;
	}
}

int	print_env(t_minishell *com_struct)
{
	t_env	*env;

	env = com_struct->env;
	while (env)
	{
		if (env->val && env->var)
			ft_printf("%s=%s\n", env->var, env->val);
		else
			ft_printf("%s\n", env->var);
		env = env->next;
	}
	return (1);
}

void	create_env(t_minishell *com_struct, char **envp)
{
	t_env	*env;
	t_env	*expo;
	int		i;

	i = 0;
	if (envp && envp[i])
	{
		env = ft_lstnewenv(envp[i]);
		expo = ft_lstnewenv(envp[i]);
		while (envp[++i])
		{
			ft_lstadd_backenv(&env, ft_lstnewenv(envp[i]));
			if (envp[i + 1])
				ft_lstinsert(&expo, ft_lstnewenv(envp[i]));
		}
		com_struct->env = env;
		com_struct->expo = expo;
		if (!case_existance(com_struct, "OLDPWD"))
			case_notexist(com_struct, "OLDPWD");
		if (!case_existance(com_struct, "PWD"))
			case_notexist(com_struct, "PWD");
	}
}

char	*get_myenv(t_minishell *com_struct, char *var)
{
	t_env	*env;
	char	*num;
	char	*final;

	env = com_struct->env;
	if (var && var[0] && var[0] == '?')
	{
		num = ft_itoa(g_exitcode);
		if (var[1])
		{
			final = ft_strjoin(num, &var[1]);
			free(num);
			return (final);
		}
		else
			return (num);
	}
	while (env)
	{
		if (ft_strcmp(env->var, var) == 0)
			return (env->val);
		env = env->next;
	}
	return (0);
}
