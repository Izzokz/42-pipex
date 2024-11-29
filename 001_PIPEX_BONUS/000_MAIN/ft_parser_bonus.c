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

static void	get_var(char **input, char **envp)
{
	char	*temp;

	temp = ft_env_var((*input) + 1, envp);
	free(*input);
	if (!temp)
		(*input) = ft_strdup("");
	else
	{
		(*input) = ft_strdup(temp);
		free(temp);
	}
}

static int	ft_get_fd0(char **argv, char **envp, t_data *data)
{
	char	*input;

	data->here_doc = gnlxio_ft_strcmp(argv[1], "here_doc") == 0;
	if (data->here_doc)
	{
		if (ft_gen_file(".here_doc", "0744") == -1)
			ft_err("Pipex:ft_parser_bonus.c:38:ft_gen_file()", -1);
		while (1)
		{
			ft_printf("here_doc > ");
			input = ft_input();
			if (!input || gnlxio_ft_strcmp(input, argv[2]) == 0)
				break ;
			else if (ft_strlen(input) > 1 && input[0] == '$')
				get_var(&input, envp);
			ft_add_line(".here_doc", input, A_END);
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
	if (argc < 5)
		return (0);
	data->fd = ft_calloc(3, sizeof(int));
	if (!data->fd)
		return (ft_free_all(data, NULL));
	data->fd[0] = ft_get_fd0(argv, envp, data);
	if (data->fd[0] < 0)
		ft_err("Pipex:ft_parser_bonus.c:62:ft_get_fd0()", 0);
	data->fd[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	if (data->fd[1] < 0)
		ft_err("Pipex:ft_parser_bonus.c:65:open()", 0);
	data->cmd = ft_calloc(argc - 2, sizeof(char **));
	if (!(data->cmd))
		return (ft_free_all(data, NULL));
	if (!ft_parse_cmds(argc, argv, data))
		return (ft_free_all(data, NULL));
	return (1);
}
