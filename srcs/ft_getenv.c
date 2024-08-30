/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:02:32 by samunyan          #+#    #+#             */
/*   Updated: 2022/09/30 22:02:36 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char **envp, const char *name)
{
	size_t	i;
	char	*val;

	i = 0;
	while (envp[i])
	{
		val = ft_strnstr(envp[i], name, ft_strlen(name));
		if (val && (*(val + ft_strlen(name)) == '='))
			return (val);
		i++;
	}
	return (NULL);
}

char	**ft_split_env(char **envp, const char *name)
{
	char	*val;
	char	**arr;

	val = ft_getenv(envp, name);
	if (!val)
	{
		err_msg(1, EINVAL, name);
		return (NULL);
	}
	val += ft_strlen(name) + 1;
	arr = ft_split(val, ':');
	return (arr);
}
