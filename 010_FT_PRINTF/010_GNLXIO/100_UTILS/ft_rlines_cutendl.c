/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rlines_cutendl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:30:11 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/23 19:30:47 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnlxio.h"

void	ft_rline_cutendl(char **rline)
{
	int	len;

	len = gnlxio_ft_strlen(*rline);
	if (len == 0)
		;
	else if ((*rline)[len - 1] == '\n')
		(*rline)[len - 1] = '\0';
}

void	ft_rlines_cutendl(char ***rlines)
{
	t_ints	ints;

	if (!rlines || !(*rlines))
		return ;
	ints.i = -1;
	while ((*rlines)[++(ints.i)])
		ft_rline_cutendl(&((*rlines)[ints.i]));
}
