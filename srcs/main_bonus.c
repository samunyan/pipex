/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:03:49 by samunyan          #+#    #+#             */
/*   Updated: 2022/09/30 22:03:51 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_s_list	*cmd_list;
	int			**pipes_fd;

	if (argc < 5)
	{
		err_msg(0, 0, USAGE_2);
		return (2);
	}
	cmd_list = parser(argc, argv);
	if (!cmd_list)
		return (EXIT_FAILURE);
	pipes_fd = create_pipes(ft_s_lstsize(cmd_list));
	if (!pipes_fd)
	{
		ft_s_lstclear(&cmd_list, free_cmd);
		exit(EXIT_FAILURE);
	}
	return (execute(cmd_list, envp, pipes_fd));
}
