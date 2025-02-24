/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:03:09 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/24 17:51:27 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_with_slash(const char *s1, const char *s2)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s2);
	free(tmp);
	return (result);
}

void	free_path_dirs(char **path_dirs)
{
	int	j;

	j = 0;
	while (path_dirs[j])
	{
		free(path_dirs[j]);
		j++;
	}
	free(path_dirs);
}

char	*find_path_access(char **path_dirs, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (path_dirs[i])
	{
		full_path = ft_strjoin_with_slash(path_dirs[i], cmd);
		if (!full_path)
		{
			free_path_dirs(path_dirs);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_path_dirs(path_dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_path_dirs(path_dirs);
	return (NULL);
}

char	*find_command_path(char *cmd, t_data *data)
{
	char	**path_dirs;
	char	*path_env;
	char	*full_path;

	if (!cmd || !data)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = find_path(data);
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	free(path_env);
	full_path = find_path_access(path_dirs, cmd);
	return (full_path);
}

char	*find_path(t_data *data)
{
	char	*path;
	int		i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(data->env[i]);
			break ;
		}
		i++;
	}
	return (path);
}
