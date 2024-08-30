/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_bin_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:19:44 by samunyan          #+#    #+#             */
/*   Updated: 2022/09/30 22:19:46 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	cmd_is_bin_path(char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		return (0);
	return (1);
}

static char	*choose_right_path(char *slashed_cmd, char **paths)
{
	char	*bin_path;
	size_t	i;

	i = 0;
	bin_path = NULL;
	while (paths[i])
	{
		bin_path = ft_strjoin(paths[i], slashed_cmd);
		if (!bin_path)
			return (NULL);
		if (access(bin_path, F_OK) == 0 || !paths[i + 1])
			break ;
		free(bin_path);
		i++;
	}
	return (bin_path);
}

char	*ft_get_bin_path(char **env, char *cmd)
{
	char	**paths;
	char	*bin_path;
	char	*slashed_cmd;

	if (!cmd)
		return (NULL);
	if (cmd_is_bin_path(cmd))
		bin_path = ft_strdup(cmd);
	else
	{
		slashed_cmd = ft_strjoin("/", cmd);
		if (!slashed_cmd)
			return (NULL);
		paths = ft_split_env(env, "PATH");
		if (!paths)
			return (NULL);
		bin_path = choose_right_path(slashed_cmd, paths);
		free(slashed_cmd);
		ft_free_arr((void **)paths);
	}
	return (bin_path);
}
