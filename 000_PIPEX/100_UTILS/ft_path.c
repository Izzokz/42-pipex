/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:11:11 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/05 12:15:07 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_get_path(char *filename, char **all_path)
{
	int		i;
	char	*path;

	path = NULL;
	i = -1;
	if (!all_path)
		return (NULL);
	while (all_path[++i])
	{
		path = ft_strjoin(all_path[i], filename);
		if (!path)
			return (NULL);
		if (access(path, X_OK) != -1)
			return (path);
		free(path);
	}
	return (NULL);
}
