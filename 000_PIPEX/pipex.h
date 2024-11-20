/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:08:21 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/10/31 10:08:22 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../010_FT_PRINTF/ft_printf.h"
# include "../020_LIBFT/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_data
{
	int		*fd;
	int		prev_tube;
	char	***cmd;
	char	**path;
}	t_data;

int		ft_err(char *msg, int value);
int		ft_process_fork(t_data *data, char **envp);
void	ft_realloc(char **buffer, unsigned int ext);
char	*ft_get_path(char *filename, char **all_path);
int		ft_free_all(t_data **data, int fd[2]);
int		ft_parse_args(int argc, char **argv, t_data **data);

#endif
