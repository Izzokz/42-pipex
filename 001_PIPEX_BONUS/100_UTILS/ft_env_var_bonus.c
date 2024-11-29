/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_var_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:42:59 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/29 16:43:01 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*ft_env_var(char *var, char **envp)
{
	char	*path_line;
	char	*temp;
	int		len;
	int		i;

	temp = ft_strdup(var);
	ft_realloc(&temp, 1);
	if (!temp)
	{
		ft_printf_err("Pipex:ft_env_var_bonus.c:22:ft_realloc()", 1);
		return (NULL);
	}
	temp[ft_strlen(temp)] = '=';
	len = ft_strlen(temp);
	path_line = NULL;
	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], temp, len))
			path_line = ft_substr(envp[i], len, -1);
	free(temp);
	return (path_line);
}
