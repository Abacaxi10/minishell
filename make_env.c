/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:11:24 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/25 21:16:10 by rabatist         ###   ########.fr       */
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
		exit(1);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
		{
			while (--i >= 0)
				free(data->env[i]);
			free(data->env);
			exit(1);
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
		exit(1);
	i = 0;
	while (env[i])
	{
		data->exp[i] = ft_strdup(env[i]);
		if (!data->exp[i])
		{
			while (--i >= 0)
				free(data->exp[i]);
			free(data->exp);
			exit(1);
		}
		i++;
	}
	data->exp[i] = NULL;
}

void	make_fake_env(t_data *data)
{
	char cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "/", 2);//pas fini
	data->env = malloc(sizeof(char *) * 3);
	if (!data->env)
		exit (1);
	data->env[0] = strdup("SHLVL=1");
	if (!data->env[0])
		exit (1);
	data->env[1] = strdup(
			"PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin:"
			"/opt/local/bin:/opt/bin"
			);
	if (!data->env[1])
		exit (1);
	data->env[2] = NULL;
}

void	make_fake_exp(t_data *data) // pas fini
{
	data->exp = malloc(sizeof(char *) * 3);
	if (!data->exp)
		exit (1);
	data->env[0] = strdup("SHLVL=1");
	if (!data->env[0])
		exit (1);
	data->env[1] = strdup(
			"PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin:"
			"/opt/local/bin:/opt/bin"
			);
	if (!data->env[1])
		exit (1);
	data->env[2] = NULL;
}
