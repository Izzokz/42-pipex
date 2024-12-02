/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:54:14 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/12/02 15:10:07 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_err(char *msg, int value, t_data *data)
{
	ft_printf_err("%s", 1, msg);
	if (data)
		ft_free_all(data, NULL);
	return (value);
}
