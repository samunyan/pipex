/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:03:58 by samunyan          #+#    #+#             */
/*   Updated: 2022/09/30 22:04:00 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*init_cmd(char *arg)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->io.type_in = STDIN;
	cmd->io.in = NULL;
	cmd->io.heredoc_delim = NULL;
	cmd->io.type_out = STDOUT;
	cmd->io.out = NULL;
	cmd->pid = 0;
	cmd->split = ft_split(arg, ' ');
	if (!cmd->split)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

int	is_heredoc(char *first_param)
{
	return (!ft_strcmp(first_param, "here_doc"));
}

t_s_list	*add_cmd_to_list(char *new_cmd, t_s_list **cmd_list)
{
	t_cmd		*cmd;
	t_s_list	*node;

	cmd = init_cmd(new_cmd);
	if (!cmd)
		return (NULL);
	node = ft_s_lstnew(cmd);
	if (!node)
	{
		free(cmd->split);
		free(cmd);
		return (NULL);
	}
	ft_s_lstadd_back(cmd_list, node);
	return (node);
}
