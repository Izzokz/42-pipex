/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:12:50 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/22 10:52:00 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static void	ft_set_path(t_data *data, char **envp)
{
	char	*path_line;
	int		i;

	data->path = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path_line = ft_substr(envp[i], 5, -1);
			if (!path_line)
				return ;
			data->path = ft_split(path_line, ':');
			free(path_line);
			i = -1;
			while (data->path[++i])
			{
				ft_realloc(&(data->path[i]), 1);
				ft_strlcat(data->path[i], "/", -1);
			}
			ft_realloc(data->path, 1);
			return ;
		}
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (!ft_parse_args(argc, argv, &data))
	{
		ft_free_all(&data, NULL);
		return (-1);
	}
	ft_set_path(&data, envp);
	if (ft_process_fork(&data, envp) == -1)
		return (-1);
	return (0);
}
