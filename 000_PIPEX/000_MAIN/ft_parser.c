/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:52:08 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/12/02 15:09:24 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	ft_parse_cmds(int argc, char **argv, t_data *data)
{
	int		i;
	int		j;

	i = 1;
	j = -1;
	while (++i < argc - 1)
	{
		data->cmd[++j] = ft_split(argv[i], ' ');
		if (!data->cmd[j])
			return (0);
	}
	return (1);
}

int	ft_parse_args(int argc, char **argv, t_data *data)
{
	if (argc != 5)
	{
		ft_printf("Error: %d arguments given while 4 are expected.", argc - 1);
		ft_printf("\nPlease, enter 1 infile, 2 commands and 1 outfile.\n");
		return (0);
	}
	data->fd = ft_calloc(3, sizeof(int));
	if (!data->fd)
		return (ft_free_all(data, NULL));
	data->fd[0] = open(argv[1], O_RDONLY);
	if (data->fd[0] < 0)
		return (ft_err("Pipex:ft_parser.c:42:open()", 0, data));
	ft_gen_file(argv[argc - 1], "0777");
	data->fd[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	if (data->fd[1] < 0)
		return (ft_err("Pipex:ft_parser.c:46:open()", 0, data));
	data->cmd = ft_calloc(argc - 2, sizeof(char **));
	if (!(data->cmd))
		return (ft_free_all(data, NULL));
	if (!ft_parse_cmds(argc, argv, data))
		return (ft_free_all(data, NULL));
	return (1);
}
