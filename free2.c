/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:18:44 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/24 18:28:19 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	int	i;

	if (data)
	{
		if (data->input)
		{
			free(data->input);
			data->input = NULL;
		}
		if (data->raw_tokens)
		{
			i = 0;
			while (data->raw_tokens[i])
			{
				free(data->raw_tokens[i]);
				data->raw_tokens[i] = NULL;
				i++;
			}
			free(data->raw_tokens);
			data->raw_tokens = NULL;
		}
	}
	free_data2(data);
	free_data3(data);
	free_data4(data);
}

void	free_data2(t_data *data)
{
	int	i;

	if (data)
	{
		if (data->env)
		{
			i = 0;
			while (data->env[i])
			{
				free(data->env[i]);
				data->env[i] = NULL;
				i++;
			}
			free(data->env);
			data->env = NULL;
		}
	}
}

void	free_data3(t_data *data)
{
	int	i;

	if (data)
	{
		if (data->exp)
		{
			i = 0;
			while (data->exp[i])
			{
				free(data->exp[i]);
				data->exp[i] = NULL;
				i++;
			}
			free(data->exp);
			data->exp = NULL;
		}
		if (data->command)
		{
			free_command(data->command);
			free(data->command);
			data->command = NULL;
		}
	}
}

void	free_data4(t_data *data)
{
	if (data)
	{
		if (data->pids)
		{
			free(data->pids);
			data->pids = NULL;
		}
		if (data->tokens)
		{
			free_tokens(data);
			data->tokens = NULL;
		}
	}
}
