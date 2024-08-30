/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:07:39 by samunyan          #+#    #+#             */
/*   Updated: 2022/09/30 22:07:41 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exit_failure_child_process(t_s_list *cmd_list, int **pipes_fd)
{
	close_pipes(pipes_fd);
	ft_s_lstclear(&cmd_list, free_cmd);
	ft_free_arr((void **)pipes_fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	set_io_for_child_process(t_s_list *cmd_list, int **pipes_fd,
									int i_child)
{
	t_cmd	*cmd;

	cmd = get_cmd(ft_s_lstnode_at(cmd_list, i_child));
	if (set_input_for_child_process(cmd, pipes_fd, i_child) < 0)
	{
		perror(cmd->io.in);
		exit_failure_child_process(cmd_list, pipes_fd);
	}
	if (set_output_for_child_process(cmd, pipes_fd, i_child) < 0)
	{
		perror(cmd->io.out);
		exit_failure_child_process(cmd_list, pipes_fd);
	}
	close_pipes(pipes_fd);
	ft_free_arr((void **)pipes_fd);
}
