/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:06:44 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/24 18:25:48 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_sub_token(t_sub_token *sub_token)
{
	if (sub_token)
	{
		if (sub_token->content)
		{
			free(sub_token->content);
			sub_token->content = NULL;
		}
		free(sub_token);
		sub_token = NULL;
	}
}

void	free_token(t_token *token)
{
	int	j;

	if (token->sub_tokens)
	{
		j = 0;
		while (token->sub_tokens[j])
		{
			free_sub_token(token->sub_tokens[j]);
			token->sub_tokens[j] = NULL;
			j++;
		}
		free(token->sub_tokens);
		token->sub_tokens = NULL;
	}
	token = NULL;
}

void	free_tokens(t_data *data)
{
	int	i;

	if (data && data->tokens)
	{
		i = 0;
		while (i < data->token_count)
		{
			free_token(&data->tokens[i]);
			if (data->tokens[i].value)
			{
				free(data->tokens[i].value);
				data->tokens[i].value = NULL;
			}
			i++;
		}
		free(data->tokens);
		data->tokens = NULL;
		data->token_count = 0;
	}
}

void	free_command(t_command *command)
{
	if (command)
	{
		if (command->args)
		{
			free(command->args);
			command->args = NULL;
		}
	}
}

void	free_all_exit(t_data *data, int exit_code)
{
	(void)data;
	free_data(data);
	printf("exit\n");
	exit(exit_code);
}
