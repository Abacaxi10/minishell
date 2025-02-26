/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_exp2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:24:51 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/26 16:43:52 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_fake_env2(t_data *data, char *cwd)
{
	data->env[3] = malloc(sizeof(char) * (ft_strlen(cwd) + 8));
	if (!data->env[3])
		free_all_exit (data, 1);
	ft_strlcpy(data->env[3], "OLDPWD=", 8);
	ft_strlcat(data->env[3], cwd, ft_strlen(cwd) + 8);
	data->env[4] = ft_strdup("_=/usr/bin/env");
	if (!data->env[4])
		free_all_exit(data, 1);
	data->env[5] = NULL;
}

void	make_fake_exp2(t_data *data, char *cwd)
{
	data->exp[3] = malloc(sizeof(char) * (ft_strlen(cwd) + 8));
	if (!data->exp[3])
		free_all_exit (data, 1);
	ft_strlcpy(data->exp[3], "OLDPWD=", 8);
	ft_strlcat(data->exp[3], cwd, ft_strlen(cwd) + 8);
	data->env[4] = ft_strdup("_=/usr/bin/env");
	if (!data->env[4])
		free_all_exit(data, 1);
	data->exp[5] = NULL;
}