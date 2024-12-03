/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_hd_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:23:46 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/12/03 13:29:26 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static void	get_var(char **input, char **envp)
{
	char	*temp;

	temp = ft_env_var(*input, envp);
	free(*input);
	if (!temp)
		(*input) = ft_strdup("");
	else
	{
		(*input) = ft_strdup(temp);
		free(temp);
	}
}

static void	ft_resplit_write(char *word, int fd, char **envp)
{
	char	**resplit;
	int		i;

	resplit = ft_split(word, '$');
	if (!resplit)
	{
		ft_printf_err("Pipex:ft_process_hd_bonus.c:39:ft_split()", 1);
		return ;
	}
	i = -1;
	if (word[0] - '$')
		ft_printf_fd("%s", fd, resplit[++i]);
	while (resplit[++i])
	{
		get_var(&(resplit[i]), envp);
		ft_printf_fd("%s", fd, resplit[i]);
	}
	ft_printf_fd(" ", fd);
	ft_free_rlines(&resplit);
}

void	ft_process_hd(char *line, char **envp)
{
	char	**split;
	t_ints	ints;

	ints.fd = open(".here_doc", O_WRONLY | O_APPEND);
	if (ints.fd < 0)
	{
		ft_printf_err("Pipex:ft_process_hd_bonus.c:63:open()", 1);
		return ;
	}
	split = ft_split(line, ' ');
	if (!split)
	{
		ft_printf_err("Pipex:ft_process_hd_bonus.c:69:ft_split()", 1);
		close(ints.fd);
		return ;
	}
	ints.i = -1;
	while (split[++(ints.i)])
		ft_resplit_write(split[ints.i], ints.fd, envp);
	ft_printf_fd("\n", ints.fd);
	ft_free_rlines(&split);
	close(ints.fd);
	return ;
}
