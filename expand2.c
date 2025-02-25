/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:35:26 by rabatist          #+#    #+#             */
/*   Updated: 2025/02/24 18:40:33 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar(t_data *data, int *i, char *str, char *result)
{
	char	*var;
	char	*env_val;
	int		j;

	(*i)++;
	var = get_var_name(str, i, &j);
	if (!var)
		return (result);
	env_val = get_env_val(var, data);
	if (!env_val)
		return (free(var), result);
	result = append_env_value(result, env_val);
	free(var);
	free(env_val);
	*i = j;
	return (result);
}

char	*no_dollar(int *i, char *str, char *result)
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

char	*manage_dollar(char *str, t_data *data)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			result = dollar_question(data, &i, result);
		else if (str[i] == '$' && (ft_isspace(str[i + 1]) == 1
				|| str[i + 1] == '\0'))
			result = only_dollar(&i, str, result);
		else if (str[i] == '$')
			result = expand_dollar(data, &i, str, result);
		else
			result = no_dollar(&i, str, result);
	}
	return (result);
}
