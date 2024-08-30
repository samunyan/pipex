/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:02:10 by samunyan          #+#    #+#             */
/*   Updated: 2022/09/30 22:02:11 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	bin_path_is_valid(char *bin_path, t_cmd *cmd)
{
	if (!cmd->split[0])
	{
		err_cmd("");
		return (127);
	}
	if (!bin_path)
	{
		err_msg(1, errno, "ft_get_bin_path()");
		return (EXIT_FAILURE);
	}
	if (access(bin_path, F_OK) != 0)
	{
		err_cmd(cmd->split[0]);
		return (127);
	}
	if (access(bin_path, X_OK) != 0)
	{
		err_perm(cmd->split[0]);
		return (126);
	}
	else
		return (EXIT_SUCCESS);
}

static void	execute_child_process(t_s_list *cmd_list, char **envp, int i_child)
{
	char	*bin_path;
	t_cmd	*cmd;
	int		ret;

	cmd = get_cmd(ft_s_lstnode_at(cmd_list, i_child));
	bin_path = ft_get_bin_path(envp, cmd->split[0]);
	ret = bin_path_is_valid(bin_path, cmd);
	if (ret != EXIT_SUCCESS)
	{
		free(bin_path);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		ft_s_lstclear(&cmd_list, free_cmd);
		exit (ret);
	}
	execve(bin_path, cmd->split, envp);
	free(bin_path);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	ft_s_lstclear(&cmd_list, free_cmd);
	exit (EXIT_FAILURE);
}

static int	supervise(int **pipes_fd, t_s_list *cmd_list)
{
	int			wstatus;
	int			pid;
	t_s_list	*tmp;

	tmp = cmd_list;
	close_pipes(pipes_fd);
	ft_free_arr((void **)pipes_fd);
	while (cmd_list)
	{
		pid = get_cmd(cmd_list)->pid;
		if (pid < 0)
			break ;
		waitpid(pid, &wstatus, 0);
		cmd_list = cmd_list->next;
	}
	ft_s_lstclear(&tmp, free_cmd);
	if (pid > 0 && WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else
		return (EXIT_FAILURE);
}

int	execute(t_s_list *cmd_list, char **envp, int **pipes_fd)
{
	int		i_child;
	int		n_cmds;
	pid_t	pid;

	i_child = 0;
	n_cmds = ft_s_lstsize(cmd_list);
	while (i_child < n_cmds)
	{
		pid = fork();
		if (pid)
		{
			get_cmd(ft_s_lstnode_at(cmd_list, i_child))->pid = pid;
			if (pid < 0)
				break ;
			i_child++;
		}
		else
		{
			set_io_for_child_process(cmd_list, pipes_fd, i_child);
			execute_child_process(cmd_list, envp, i_child);
		}
	}
	return (supervise(pipes_fd, cmd_list));
}
