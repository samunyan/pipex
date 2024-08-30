/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:04:27 by samunyan          #+#    #+#             */
/*   Updated: 2022/09/30 22:04:28 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "string.h"
# include "errno.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# define STDIN					0
# define HEREDOC				1
# define REDIR_INPUT			2
# define STDOUT					0
# define REDIR_OUTPUT			3
# define REDIR_OUTPUT_APPEND	4

# define USAGE_1	"Usage: ./pipex [file1] [cmd1] [cmd2] [file2]" \
					"\n\t(behaves like \" < file1 cmd1 | cmd2 > file2 \")"
# define USAGE_2	"Usage: ./pipex [file1] [cmd1] [cmd2] [...] [file2]" \
					"\n\t(behaves like \" < file1 cmd1 | cmd2 | [...] > file2 \")"
# define READ	0
# define WRITE	1

# define THD	".heredoc_tmp"

typedef struct s_redir
{
	int		type_in;
	char	*in;
	char	*heredoc_delim;
	int		type_out;
	char	*out;
}	t_redir;

typedef struct s_cmd
{
	char	**split;
	t_redir	io;
	int		pid;
}	t_cmd;

t_s_list	*parser(int argc, char **argv);
t_cmd		*init_cmd(char *arg);
int			is_heredoc(char *first_param);
t_s_list	*add_cmd_to_list(char *new_cmd, t_s_list **cmd_list);
int			**create_pipes(int n_cmds);
void		close_pipes(int **pipes_fd);
int			execute(t_s_list *cmd_list, char **envp, int **pipes_fd);
void		set_io_for_child_process(t_s_list *cmd_list, int **pipes_fd,
				int i_child);
int			set_input_for_child_process(t_cmd *cmd, int **pipes_fd,
				int i_child);
int			set_output_for_child_process(t_cmd *cmd, int **pipes_fd,
				int i_child);
char		*ft_getenv(char **env, const char *var_name);
char		**ft_split_env(char **envp, const char *name);
char		*ft_get_bin_path(char **envp, char *bin);
int			dup2_and_close_oldfd(int oldfd, int newfd);
void		free_cmd(void *cmd);
t_cmd		*get_cmd(t_s_list *cmd_node);
void		err_msg(int errnoflag, int errnum, const char *msg);
void		err_cmd(const char *cmd);
void		err_perm(const char *cmd);
#endif
