/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:40:44 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/08 09:40:45 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <sys/wait.h>

static void	redirect_fd(t_data *data, int *tube, int i)
{
	if (data->prev_tube != -1)
		dup2(data->prev_tube, 0);
	else
		dup2(data->fd[0], 0);
	if (!data->cmd[i + 1])
		dup2(data->fd[1], 1);
	else
		dup2(tube[1], 1);
	ft_free_all(NULL, tube);
	if (data->prev_tube != -1)
		close (data->prev_tube);
}

static int	do_fork(t_data *data, int *tube, int i, char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (ft_err("Pipex:ft_process.c:35:fork()", -1));
	if (pid == 0)
	{
		redirect_fd(data, tube, i);
		execve(ft_get_path(data->cmd[i][0], data->path), data->cmd[i], envp);
		ft_free_all(&data, tube);
		ft_printf_err("Pipex:ft_process.c:41:execve()", 1);
		exit(127);
	}
	close(tube[1]);
	return (0);
}

static void	ft_pipe_swap(int tube[2], int *prev_tube, int terminate)
{
	if (*prev_tube != -1)
		close(*prev_tube);
	if (terminate)
		return ;
	*prev_tube = tube[0];
	close(tube[1]);
}

int	ft_process_fork(t_data *data, char **envp)
{
	int	i;
	int	tube[2];

	i = -1;
	data->prev_tube = -1;
	while (data->cmd[++i])
	{
		if (pipe(tube) < 0)
		{
			ft_free_all(&data, NULL);
			return (ft_err("Pipex:ft_process.c:69:pipe()", -1));
		}
		if (do_fork(data, tube, i, envp) == -1)
		{
			ft_free_all(&data, tube);
			return (ft_err("Pipex:ft_process.c:74:do_fork()", -1));
		}
		ft_pipe_swap(tube, &(data->prev_tube), 0);
	}
	ft_pipe_swap(tube, &(data->prev_tube), 1);
	while (wait(NULL) > 0)
		;
	ft_free_all(&data, tube);
	return (0);
}