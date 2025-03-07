/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:51:27 by nbonnet           #+#    #+#             */
/*   Updated: 2025/02/27 17:08:35 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (data->pids[i] != -1)
		waitpid(data->pids[i++], &status, 0);
}

void	run_child_process(t_data *data, char *cmd_path, int is_builtin_cmd)
{
	if (data->command->input_fd != STDIN_FILENO)
		dup2(data->command->input_fd, STDIN_FILENO);
	if (data->command->output_fd != STDOUT_FILENO)
		dup2(data->command->output_fd, STDOUT_FILENO);
	else if (data->command->fd_out != -1)
		dup2(data->command->fd_out, STDOUT_FILENO);
	if (data->prev_pipe_read_end != -1)
		close(data->prev_pipe_read_end);
	if (is_builtin_cmd)
		exec_builtins(data);
	else
		execve(cmd_path, data->command->args, data->env);
	exit(1);
}

void	cleanup_parent(t_data *data)
{
	if (data->command->fd_out != -1)
		close(data->command->fd_out);
	if (data->command->input_fd != STDIN_FILENO)
		close(data->command->input_fd);
	if (data->command->output_fd != STDOUT_FILENO)
		close(data->command->output_fd);
	if (data->command->error_pipe_write != -1)
		close(data->command->error_pipe_write);
}

void	setup_pipe(t_data *data, int pipe_fd[2])
{
	int	error_pipe[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	if (pipe(error_pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}
	data->prev_pipe_read_end = pipe_fd[0];
	data->command->fd_out = pipe_fd[1];
	data->command->error_pipe_read = error_pipe[0];
	data->command->error_pipe_write = error_pipe[1];
}

void	prepare_pipe_connection(t_data *data)
{
	int	pipe_fd[2];

	if (data->current_token < data->token_count
		&& data->tokens[data->current_token].type == TOKEN_PIPE
		&& data->command->output_fd == STDOUT_FILENO)
		setup_pipe(data, pipe_fd);
	else
		data->command->fd_out = -1;
}
