/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:08:38 by samunyan          #+#    #+#             */
/*   Updated: 2022/09/30 22:08:40 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_input_for_heredoc(char *delim, int fd_in)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			break ;
		}
		line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd_in);
		free(line);
	}
}

static int	gather_heredoc(t_cmd *cmd)
{
	int	fd_in;

	fd_in = open(cmd->io.in, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_in < 0)
		return (-1);
	get_input_for_heredoc(cmd->io.heredoc_delim, fd_in);
	if (close(fd_in) < 0)
		return (-1);
	fd_in = open(cmd->io.in, O_RDONLY);
	if (fd_in < 0)
		return (-1);
	unlink(cmd->io.in);
	return (fd_in);
}

int	set_input_for_child_process(t_cmd *cmd, int **pipes_fd, int i_child)
{
	int	fd_in;

	if (cmd->io.type_in == REDIR_INPUT)
		fd_in = open(cmd->io.in, O_RDONLY);
	if (cmd->io.type_in == HEREDOC)
		fd_in = gather_heredoc(cmd);
	if (cmd->io.type_in == STDIN)
		fd_in = pipes_fd[i_child - 1][READ];
	if (fd_in < 0)
		return (fd_in);
	return (dup2_and_close_oldfd(fd_in, STDIN_FILENO));
}

int	set_output_for_child_process(t_cmd *cmd, int **pipes_fd, int i_child)
{
	int	fd_out;

	if (cmd->io.type_out == REDIR_OUTPUT)
		fd_out = open(cmd->io.out, O_WRONLY | O_CREAT
				| O_CLOEXEC | O_TRUNC, 0666);
	if (cmd->io.type_out == REDIR_OUTPUT_APPEND)
		fd_out = open(cmd->io.out, O_WRONLY | O_CREAT
				| O_CLOEXEC | O_APPEND, 0666);
	if (cmd->io.type_out == STDOUT)
		fd_out = pipes_fd[i_child][WRITE];
	if (fd_out < 0)
		return (fd_out);
	return (dup2_and_close_oldfd(fd_out, STDOUT_FILENO));
}
