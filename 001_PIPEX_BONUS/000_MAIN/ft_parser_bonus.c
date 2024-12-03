/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:52:08 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/22 10:51:49 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static int	ft_parse_cmds(int argc, char **argv, t_data *data)
{
	int		i;
	int		j;

	i = 1;
	if (data->here_doc)
		i += 1;
	j = -1;
	while (++i < argc - 1)
	{
		data->cmd[++j] = ft_split(argv[i], ' ');
		if (!data->cmd[j])
			return (0);
	}
	return (1);
}

static int	ft_get_fd0(char **argv, char **envp, t_data *data)
{
	char	*input;

	if (data->here_doc)
	{
		if (ft_gen_file(".here_doc", "0744") == -1)
			ft_err("Pipex:ft_parser_bonus.c:39:ft_gen_file()", -1, NULL);
		while (1)
		{
			ft_printf("here_doc > ");
			input = ft_input();
			if (!input || gnlxio_ft_strcmp(input, argv[2]) == 0)
				break ;
			ft_process_hd(input, envp);
			free(input);
			input = NULL;
		}
		free(input);
		return (open(".here_doc", O_RDONLY));
	}
	return (open(argv[1], O_RDONLY));
}

int	ft_parse_args(int argc, char **argv, char **envp, t_data *data)
{
	if (argc - 2 - data->here_doc < 3)
	{
		ft_printf("Error: After some calculations, something is missing\n");
		return (0);
	}
	data->fd = ft_calloc(3, sizeof(int));
	if (!data->fd)
		return (ft_free_all(data, NULL));
	data->fd[0] = ft_get_fd0(argv, envp, data);
	if (data->fd[0] < 0)
		return (ft_err("Pipex:ft_parser_bonus.c:67:ft_get_fd0()", 0, data));
	ft_gen_file(argv[argc - 1], "0777");
	if (data->here_doc)
		data->fd[1] = open(argv[argc - 1], O_WRONLY | O_APPEND);
	else
		data->fd[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	if (data->fd[1] < 0)
		return (ft_err("Pipex:ft_parser_bonus.c:72||74:open()", 0, data));
	data->cmd = ft_calloc(argc - 2 - data->here_doc, sizeof(char **));
	if (!(data->cmd))
		return (ft_free_all(data, NULL));
	if (!ft_parse_cmds(argc, argv, data))
		return (ft_free_all(data, NULL));
	return (1);
}
