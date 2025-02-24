/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbonnet <nbonnet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:56:58 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/24 17:50:42 by nbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_exec(t_data *data)
{
	while (data->current_token < data->token_count)
	{
		if (parse_command(data) != 0)
		{
			while (data->current_token < data->token_count
				&& data->tokens[data->current_token].type != TOKEN_PIPE)
				data->current_token++;
			if (data->current_token < data->token_count
				&& data->tokens[data->current_token].type == TOKEN_PIPE)
				data->current_token++;
			continue ;
		}
		if (execute_command(data) != 0)
			return (1);
		if (data->command)
		{
			free_command(data->command);
			free(data->command);
			data->command = NULL;
		}
		if (data->current_token < data->token_count
			&& data->tokens[data->current_token].type == TOKEN_PIPE)
			data->current_token++;
	}
	return (0);
}

int	process_command_line(t_data *data)
{
	g_signals(1);
	data->pid_index = 0;
	data->pids = malloc(sizeof(pid_t) * (data->token_count + 1));
	if (!data->pids)
		return (1);
	init_pid_list(data);
	if (start_exec(data) == 1)
		return (1);
	wait_for_children(data);
	g_signals(0);
	return (0);
}

void	start_fork(t_data *data, char *cmd_path, int is_builtin_cmd)
{
	data->pid = fork();
	if (data->pid < 0)
	{
		free(cmd_path);
		data->exit_status = 1;
		return ;
	}
	data->pids[data->pid_index++] = data->pid;
	if (data->pid == 0)
		run_child_process(data, cmd_path, is_builtin_cmd);
	else
		cleanup_parent(data);
}

int	check_path(t_data *data)
{
	struct stat	st;

	data->cmd_path = find_command_path(data->command->args[0], data);
	if (!data->cmd_path)
	{
		data->exit_status = 127;
		print_first_error(data->command->args[0]);
		return (1);
	}
	else
	{
		if (stat(data->cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_putstr_fd(data->command->args[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			data->exit_status = 126;
			free(data->cmd_path);
			return (1);
		}
	}
	return (0);
}

int	execute_command(t_data *data)
{
	int	is_builtin_cmd;

	if (!data->command->args[0] || data->command->args[0][0] == '\0')
		return (0);
	prepare_pipe_connection(data);
	is_builtin_cmd = is_builtin(data);
	if (is_builtin_cmd && data->command->input_fd == STDIN_FILENO
		&& data->command->output_fd == STDOUT_FILENO
		&& data->command->fd_out == -1
		&& data->prev_pipe_read_end == -1)
	{
		exec_builtins(data);
		return (0);
	}
	if (is_builtin_cmd)
		data->cmd_path = NULL;
	else
		if (check_path(data) == 1)
			return (1);
	data->exit_status = 0;
	start_fork(data, data->cmd_path, is_builtin_cmd);
	free(data->cmd_path);
	return (0);
}
