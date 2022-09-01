/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:44:15 by mfirdous          #+#    #+#             */
/*   Updated: 2022/07/16 12:43:18 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	int		sign;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		write(fd, "-", 1);
	}
	if (n >= 10 || n <= -10)
	{
		digit = sign * (n % 10) + 48;
		ft_putnbr_fd(sign * (n / 10), fd);
		write(fd, &digit, 1);
	}
	if (n < 10 && n > -10)
	{			
		digit = sign * n + 48;
		write(fd, &digit, 1);
	}
}
