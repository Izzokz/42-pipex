/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:07:36 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/12/02 15:10:25 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_realloc(char **buffer, unsigned int ext)
{
	char	*temp_buffer;

	if (!ext || !(*buffer))
		return ;
	temp_buffer = ft_strdup(*buffer);
	if (!temp_buffer)
		return ;
	free(*buffer);
	*buffer = ft_calloc(ft_strlen(temp_buffer) + ext + 1, sizeof(char));
	if (!(*buffer))
	{
		free(temp_buffer);
		return ;
	}
	ft_strlcat(*buffer, temp_buffer, -1);
	free(temp_buffer);
}
