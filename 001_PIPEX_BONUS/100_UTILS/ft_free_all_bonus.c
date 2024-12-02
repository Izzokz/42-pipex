/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:14:36 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/22 10:52:14 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static void	ft_close_all(t_data *data, int fd[2])
{
	if (data->fd)
	{
		if (data->fd[0] > 2)
			close(data->fd[0]);
		if (data->fd[1] > 2)
			close(data->fd[1]);
		free(data->fd);
		data->fd = NULL;
	}
	if (fd)
	{
		if (fd[0] > 2)
			close(fd[0]);
		if (fd[1] > 2)
			close(fd[1]);
	}
	return ;
}

static void	ft_free_chain(char ***chain)
{
	int	i;

	if (!chain || !(*chain))
		return ;
	i = -1;
	while ((*chain)[++i])
	{
		free((*chain)[i]);
		(*chain)[i] = NULL;
	}
	free(*chain);
	*chain = NULL;
}

static void	ft_free_cmds_path(t_data *data)
{
	int	i;

	if (!data->cmd)
		return ;
	i = -1;
	while (data->cmd[++i])
		ft_free_chain(&data->cmd[i]);
	free(data->cmd);
	data->cmd = NULL;
	if (!data->path)
		return ;
	i = -1;
	while (data->path[++i])
	{
		free(data->path[i]);
		data->path[i] = NULL;
	}
	free(data->path);
	data->path = NULL;
}

int	ft_free_all(t_data *data, int fd[2])
{
	if (!data)
		return (0);
	ft_free_cmds_path(data);
	ft_close_all(data, fd);
	if (data->here_doc)
		unlink(".here_doc");
	return (0);
}
