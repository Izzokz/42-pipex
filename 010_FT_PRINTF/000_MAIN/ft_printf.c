/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:47:35 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/10/17 15:08:36 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*
Parameters:
	- const char *str;
	- int fd;
	- (args);
Behaviour:
	Acts like dprintf() with more format specifiers.
	NOTE : Every format specifier is explained on GitHub
Returns:
	Number of printed characters
*/
int	ft_printf_fd(const char *str, int fd, ...)
{
	t_params	*pa;

	if (!str || fd < 0)
		return (-1);
	pa = ft_calloc(1, sizeof(t_params));
	pa->str = str;
	pa->fd = fd;
	pa->i = -1;
	va_start(pa->args, fd);
	return (ft_process(pa));
}

/*
Parameters:
	- const char *str;
	- (args);
Behaviour:
	Acts like printf() with more format specifiers.
	NOTE : Every format specifier is explained on GitHub
Returns:
	Number of printed characters
*/
int	ft_printf(const char *str, ...)
{
	t_params	*pa;

	if (!str)
		return (-1);
	pa = ft_calloc(1, sizeof(t_params));
	pa->str = str;
	pa->fd = 1;
	pa->i = -1;
	va_start(pa->args, str);
	return (ft_process(pa));
}

static int	ft_strerr(int errid, int fd)
{
	int		len;
	char	*line;

	line = ft_get_line("/var/tmp/.errmsg", errid + 1);
	len = ft_printf_fd("%s\n", fd, line);
	free(line);
	line = NULL;
	return (len);
}

/*
Parameters:
	- const char *msg;
	- int fd;
	- (args);
Behaviour:
	Will print "<msg>: " before printing the error.
	NOTE : <fd> is necessary because it is usually used in log files.
Returns:
	Number of printed characters
Examples:
	ft_printf_err(NULL, 0) >>> "Remote I/O error"
	ft_printf_err("err", 0) >>> "err: Socket type not supported"
	ft_printf_err("errid[%d]", 0, i) >>> "errid[778]: Success"
*/
int	ft_printf_err(const char *msg, int fd, ...)
{
	t_params	*pa;
	int			len;

	pa = ft_calloc(1, sizeof(t_params));
	pa->str = msg;
	pa->fd = fd;
	pa->i = -1;
	va_start(pa->args, fd);
	len = 0;
	if (msg)
	{
		len += ft_process(pa);
		len += write(fd, ": ", 2);
	}
	else
	{
		va_end(pa->args);
		free(pa);
	}
	len += ft_strerr(errno, fd);
	return (len);
}