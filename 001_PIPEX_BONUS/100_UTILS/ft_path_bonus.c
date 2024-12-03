/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:11:11 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/22 10:52:20 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*ft_get_path(char *filename, char **all_path)
{
	int		i;
	char	*path;

	path = NULL;
	i = -1;
	if (!all_path)
		return (NULL);
	if (filename[0] == '/')
		if (access(filename, X_OK) != -1)
			return (ft_strdup(filename));
	while (all_path[++i])
	{
		path = ft_strjoin(all_path[i], filename);
		if (!path)
			return (NULL);
		if (access(path, X_OK) != -1)
			return (path);
		free(path);
	}
	ft_printf_err("Pipex:%s (access=%_1)", 1, filename, 0);
	return (NULL);
}
