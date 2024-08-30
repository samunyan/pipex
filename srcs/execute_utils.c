/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:02:18 by samunyan          #+#    #+#             */
/*   Updated: 2022/09/30 22:02:19 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int **pipes_fd)
{
	int	i;

	i = 0;
	while (pipes_fd[i])
	{
		close(pipes_fd[i][READ]);
		close(pipes_fd[i][WRITE]);
		i++;
	}
}

int	**create_pipes(int n_cmds)
{
	int	**pipes_fd;
	int	i;

	pipes_fd = malloc(sizeof(int *) * ((n_cmds)));
	if (!(pipes_fd))
		return (NULL);
	i = 0;
	while (i < n_cmds - 1)
	{
		pipes_fd[i] = malloc(sizeof(int) * 2);
		{
			if (!pipes_fd[i] || pipe(pipes_fd[i]) < 0)
			{
				pipes_fd[i] = NULL;
				close_pipes(pipes_fd);
				ft_free_arr_until((void **)pipes_fd, i);
				return (NULL);
			}
		}
		i++;
	}
	pipes_fd[i] = NULL;
	return (pipes_fd);
}

int	dup2_and_close_oldfd(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (1);
	if (dup2(oldfd, newfd) == -1)
		return (-1);
	close(oldfd);
	return (1);
}
