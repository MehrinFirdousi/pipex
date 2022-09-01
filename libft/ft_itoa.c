/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:07:45 by mfirdous          #+#    #+#             */
/*   Updated: 2022/07/16 12:40:23 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		sign;
	char	buf[12];

	sign = 1;
	i = 12;
	buf[--i] = 0;
	if (n == 0)
		buf[--i] = 48;
	if (n < 0)
		sign = -1;
	while (n != 0)
	{
		buf[--i] = sign * (n % 10) + 48;
		n /= 10;
	}
	if (sign == -1)
		buf[--i] = '-';
	str = (char *)malloc((12 - i) * sizeof(char));
	if (str)
		ft_strlcpy(str, buf + i, 12 - i);
	return (str);
}
