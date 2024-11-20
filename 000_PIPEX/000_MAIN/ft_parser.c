/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:52:08 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/10/31 12:52:09 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	ft_parse_cmds(int argc, char **argv, t_data **data)
{
	int		i;
	int		j;

	i = 1;
	j = -1;
	while (++i < argc - 1)
	{
		(*data)->cmd[++j] = ft_split(argv[i], ' ');
		if (!(*data)->cmd[j])
			return (0);
	}
	return (1);
}

int	ft_parse_args(int argc, char **argv, t_data **data)
{
	if (argc < 5)
		return (0);
	*data = ft_calloc(2, sizeof(t_data));
	if (!(*data))
		return (0);
	(*data)->fd = ft_calloc(3, sizeof(int));
	if (!(*data)->fd)
		return (ft_free_all(data, NULL));
	(*data)->fd[0] = open(argv[1], O_RDONLY);
	if ((*data)->fd[0] < 0)
		ft_err("Pipex:ft_parser.c:41:open()", -1);
	(*data)->fd[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	if ((*data)->fd[1] < 0)
		ft_err("Pipex:ft_parser.c:44:open()", -1);
	(*data)->cmd = ft_calloc(argc - 2, sizeof(char **));
	if (!((*data)->cmd))
		return (ft_free_all(data, NULL));
	if (!ft_parse_cmds(argc, argv, data))
		return (ft_free_all(data, NULL));
	return (1);
}
