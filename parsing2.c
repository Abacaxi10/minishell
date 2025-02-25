/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:38:27 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/24 19:05:25 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_sub_token(t_data *data, t_token *token, int j)
{
	char	*tmp;
	char	*new_tmp;

	tmp = ft_strdup("");
	if (!tmp)
	{
		free(data->content);
		return (1);
	}
	while (token->sub_tokens && token->sub_tokens[j])
	{
		new_tmp = ft_strjoin(tmp, token->sub_tokens[j]->content);
		if (!new_tmp)
		{
			free(tmp);
			free(data->content);
			return (1);
		}
		free(tmp);
		tmp = new_tmp;
		j++;
	}
	token->value = tmp;
	return (0);
}

void	free_sub_tokens(t_token *token)
{
	int	j;

	if (!token->sub_tokens)
		return ;
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
