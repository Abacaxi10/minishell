/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:11:24 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/26 16:41:26 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		free_all_exit(data, 1);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
		{
			while (--i >= 0)
				free(data->env[i]);
			free(data->env);
			free_all_exit(data, 1);
		}
		i++;
	}
	data->env[i] = NULL;
}

void	make_exp(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->exp = malloc(sizeof(char *) * (i + 1));
	if (!data->exp)
		free_all_exit(data, 1);
	i = 0;
	while (env[i])
	{
		data->exp[i] = ft_strdup(env[i]);
		if (!data->exp[i])
		{
			while (--i >= 0)
				free(data->exp[i]);
			free(data->exp);
			free_all_exit(data, 1);
		}
		i++;
	}
	data->exp[i] = NULL;
}

void	make_fake_env(t_data *data)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "/", 2);
	data->env = malloc(sizeof(char *) * 6);
	if (!data->env)
		free_all_exit (data, 1);
	data->env[0] = strdup("SHLVL=1");
	if (!data->env[0])
		free_all_exit (data, 1);
	data->env[1] = strdup(
			"PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin:"
			"/opt/local/bin:/opt/bin");
	if (!data->env[1])
		free_all_exit (data, 1);
	data->env[2] = malloc(sizeof(char) * (ft_strlen(cwd) + 5));
	if (!data->env[2])
		free_all_exit (data, 1);
	ft_strlcpy(data->env[2], "PWD=", 5);
	ft_strlcat(data->env[2], cwd, ft_strlen(cwd) + 5);
	make_fake_env2(data, cwd);
}

void	make_fake_exp(t_data *data)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "/", 2);
	data->exp = malloc(sizeof(char *) * 6);
	if (!data->exp)
		free_all_exit (data, 1);
	data->exp[0] = strdup("SHLVL=1");
	if (!data->exp[0])
		free_all_exit (data, 1);
	data->exp[1] = strdup(
			"PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin:"
			"/opt/local/bin:/opt/bin");
	if (!data->exp[1])
		free_all_exit (data, 1);
	data->exp[2] = malloc(sizeof(char) * (ft_strlen(cwd) + 5));
	if (!data->exp[2])
		free_all_exit (data, 1);
	ft_strlcpy(data->exp[2], "PWD=", 5);
	ft_strlcat(data->exp[2], cwd, ft_strlen(cwd) + 5);
	make_fake_exp2(data, cwd);
}
