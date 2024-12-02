/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:54:14 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/22 10:52:09 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	ft_err(char *msg, int value, t_data *data)
{
	ft_printf_err("%s", 1, msg);
	if (data)
		ft_free_all(data, NULL);
	return (value);
}
