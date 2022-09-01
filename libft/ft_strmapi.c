/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:07:39 by mfirdous          #+#    #+#             */
/*   Updated: 2022/07/17 17:53:08 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*res;

	if (!s)
		return (0);
	len = ft_strlen(s);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res)
	{
		res[len] = 0;
		while (--len >= 0)
			res[len] = f(len, s[len]);
	}
	return (res);
}
