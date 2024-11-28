/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:28:44 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/28 12:28:47 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != 0)
		len++;
	return (len);
}

int	ft_printstr(char *str)
{
	int	counter;

	if (!str)
		counter = write(1, "(null)", 6);
	else
		counter = write(1, str, ft_strlen(str));
	if (counter < 0)
		return (-1);
	else
		return (counter);
}
