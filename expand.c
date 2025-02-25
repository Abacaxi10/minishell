/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:24 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/24 18:40:11 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_question(t_data *data, int *i, char *result)
{
	char	*exit_str;
	char	*tmp;

	exit_str = ft_itoa(data->exit_status);
	if (!exit_str)
		return (result);
	tmp = ft_strjoin(result, exit_str);
	if (!tmp)
	{
		free(exit_str);
		return (result);
	}
	free(result);
	result = tmp;
	free(exit_str);
	(*i) += 2;
	return (result);
}

char	*only_dollar(int *i, char *str, char *result)
{
	char	buf[2];
	char	*tmp;

	buf[0] = str[(*i)];
	buf[1] = '\0';
	tmp = ft_strjoin(result, buf);
	if (!tmp)
		return (result);
	free(result);
	result = tmp;
	(*i)++;
	return (result);
}

char	*get_var_name(char *str, int *i, int *j)
{
	char	*var;

	*j = *i;
	while (str[*j] && (ft_isalnum(str[*j]) || str[*j] == '_'))
		(*j)++;
	var = ft_substr(str, *i, *j - *i);
	return (var);
}

char	*get_env_val(char *var, t_data *data)
{
	char	*env_val;

	env_val = get_env_value(var, data);
	if (!env_val)
		env_val = ft_strdup("");
	return (env_val);
}

char	*append_env_value(char *result, char *env_val)
{
	char	*tmp;

	tmp = ft_strjoin(result, env_val);
	if (!tmp)
		return (result);
	free(result);
	return (tmp);
}
