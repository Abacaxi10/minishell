/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sub_token2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:39:00 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/24 20:39:32 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sub_token_quotes2(t_token *token, t_data *data, char quote_type,
		int *sub_token_count)
{
	char	*temp;

	if (!token->sub_tokens[*sub_token_count]->content)
	{
		free(token->sub_tokens[*sub_token_count]);
		token->sub_tokens[*sub_token_count] = NULL;
		return (1);
	}
	if (quote_type == '"')
	{
		temp = manage_dollar(token->sub_tokens[*sub_token_count]->content,
				data);
		if (temp != token->sub_tokens[*sub_token_count]->content)
		{
			free(token->sub_tokens[*sub_token_count]->content);
			token->sub_tokens[*sub_token_count]->content = temp;
		}
	}
	(*sub_token_count)++;
	return (0);
}

void	sub_token_quotes(t_token *token, t_data *data, int *i,
		int *sub_token_count)
{
	int		start;
	char	quote_type;

	quote_type = data->content[(*i)++];
	start = *i;
	while (data->content[*i] && data->content[*i] != quote_type)
		(*i)++;
	token->sub_tokens[*sub_token_count] = malloc(sizeof(t_sub_token));
	if (!token->sub_tokens[*sub_token_count])
		return ;
	if (quote_type == '\'')
		token->sub_tokens[*sub_token_count]->type = TOKEN_SQUOTE;
	else if (quote_type == '"')
		token->sub_tokens[*sub_token_count]->type = TOKEN_DQUOTE;
	token->sub_tokens[*sub_token_count]->content = ft_substr(data->content,
			start, *i - start);
	if (sub_token_quotes2(token, data, quote_type, sub_token_count) == 1)
		return ;
	if (data->content[*i] == quote_type)
		(*i)++;
}
