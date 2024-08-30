/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:04:04 by samunyan          #+#    #+#             */
/*   Updated: 2022/09/30 22:04:06 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd(void *cmd)
{
	ft_free_arr((void **)((t_cmd *)cmd)->split);
	free(cmd);
}

t_cmd	*get_cmd(t_s_list *cmd_node)
{
	return ((t_cmd *)cmd_node->content);
}

void	err_perm(const char *cmd)
{
	ft_dprintf(STDERR_FILENO, "%s: Permission denied\n", cmd);
}

void	err_cmd(const char *cmd)
{
	ft_dprintf(STDERR_FILENO, "%s: command not found\n", cmd);
}

void	err_msg(int errnoflag, int errnum, const char *msg)
{
	if (errnoflag)
		ft_dprintf(STDERR_FILENO, "%s: %s\n", msg, strerror(errnum));
	else
		ft_dprintf(STDERR_FILENO, "%s\n", msg);
}
