/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 12:39:35 by mfirdous          #+#    #+#             */
/*   Updated: 2022/07/16 19:16:21 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		slen;
	char	ch;

	slen = 0;
	ch = (char)c;
	while (s[slen])
		slen++;
	if (!ch && !s[slen])
		return ((char *)&s[slen]);
	while (slen >= 0)
	{
		if (s[slen] == ch)
			return ((char *)&s[slen]);
		slen--;
	}
	return (0);
}
