/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:28:25 by mfirdous          #+#    #+#             */
/*   Updated: 2022/07/17 22:40:51 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_from_set(char c, char *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start;
	int		end;
	int		i;

	if (!s1)
		return (ft_strdup(""));
	i = 0;
	while (s1[i] && is_from_set(s1[i], (char *)set))
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (i >= 0 && is_from_set(s1[i], (char *)set))
		i--;
	end = i;
	res = ft_substr(s1, start, end - start + 1);
	if (!res)
		return (0);
	return (res);
}
