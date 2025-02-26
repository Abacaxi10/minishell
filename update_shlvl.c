/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:50:58 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/26 18:08:03 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl_env(t_data *data)
{
	int	i;
	char *shlvl;

	shlvl = NULL;
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "SHLVL=", 6) == 0)
		{
			shlvl = data->env[i];
			break ;
		}
		i++;
	}
	if (shlvl == NULL)
	{
		data->env[i] = malloc(9);
		if (!data->env[i])
			free_all_exit(data, 1);
		ft_strlcpy(data->env[i], "SHLVL=1", 8);
		data->env[i + 1] = NULL;
	}
	else
		increase_shlvl_env(data, shlvl, i);
}

void	increase_shlvl_env(t_data *data, char *shlvl, int i)
{
	int		lvl;
	char	*new_lvl;

	lvl = atoi(shlvl + 6);
	lvl++;
	new_lvl = ft_itoa(lvl);
	if (!new_lvl)
	{
		free (new_lvl);
		free_all_exit(data, 1);
	}
	free (data->env[i]);
	data->env[i] = malloc(ft_strlen(new_lvl) + 7);
	if (!data->env[i])
	{
		free (new_lvl);
		free_all_exit(data, 1);
	}
	ft_strlcpy(data->env[i], "SHLVL=", 7);
	ft_strlcat(data->env[i], new_lvl, ft_strlen(new_lvl) + 7);
	free (new_lvl);
}

void	update_shlvl_exp(t_data *data)
{
	int	i;
	char *shlvl;

	shlvl = NULL;
	i = 0;
	while (data->exp[i])
	{
		if (ft_strncmp(data->exp[i], "SHLVL=", 6) == 0)
		{
			shlvl = data->exp[i];
			break ;
		}
		i++;
	}
	if (shlvl == NULL)
	{
		data->exp[i] = malloc(9);
		if (!data->exp[i])
			free_all_exit(data, 1);
		ft_strlcpy(data->exp[i], "SHLVL=1", 8);
		data->exp[i + 1] = NULL;
	}
	else
		increase_shlvl_exp(data, shlvl, i);
}

void	increase_shlvl_exp(t_data *data, char *shlvl, int i)
{
	int		lvl;
	char	*new_lvl;

	lvl = atoi(shlvl + 6);
	lvl++;
	new_lvl = ft_itoa(lvl);
	if (!new_lvl)
	{
		free (new_lvl);
		free_all_exit(data, 1);
	}
	free (data->exp[i]);
	data->exp[i] = malloc(ft_strlen(new_lvl) + 7);
	if (!data->exp[i])
	{
		free (new_lvl);
		free_all_exit(data, 1);
	}
	ft_strlcpy(data->exp[i], "SHLVL=", 7);
	ft_strlcat(data->exp[i], new_lvl, ft_strlen(new_lvl) + 7);
	free (new_lvl);
}
