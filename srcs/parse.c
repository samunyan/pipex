/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:03:53 by samunyan          #+#    #+#             */
/*   Updated: 2022/09/30 22:03:55 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_s_list	*parse_args(int n, char **args)
{
	t_s_list	*cmd_list;
	int			i;

	cmd_list = NULL;
	i = 0;
	while (i < n)
	{
		if (!add_cmd_to_list(args[i], &cmd_list))
		{
			ft_s_lstclear(&cmd_list, free_cmd);
			return (NULL);
		}
		i++;
	}
	return (cmd_list);
}

static void	parse_io(t_s_list *cmd_list, int argc, char **argv)
{
	t_cmd	*first;
	t_cmd	*last;

	first = get_cmd(cmd_list);
	last = get_cmd(ft_s_lstlast(cmd_list));
	if (argc > 4 && is_heredoc(argv[0]))
	{
		first->io.type_in = HEREDOC;
		first->io.in = THD;
		first->io.heredoc_delim = argv[1];
		last->io.type_out = REDIR_OUTPUT_APPEND;
		last->io.out = argv[argc - 1];
	}
	else
	{
		first->io.type_in = REDIR_INPUT;
		first->io.in = argv[0];
		last->io.type_out = REDIR_OUTPUT;
		last->io.out = argv[argc - 1];
	}
}

t_s_list	*parser(int argc, char **argv)
{
	t_s_list	*cmd_list;

	if (argc > 5 && is_heredoc(argv[1]))
		cmd_list = parse_args(argc - 4, argv + 3);
	else
		cmd_list = parse_args(argc - 3, argv + 2);
	parse_io(cmd_list, argc - 1, argv + 1);
	return (cmd_list);
}
