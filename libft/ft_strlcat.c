/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:40:23 by mfirdous          #+#    #+#             */
/*   Updated: 2022/07/17 14:58:10 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	if (!dst && !src)
		return (0);
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	dest_len = i;
	j = 0;
	while ((i < dstsize - 1) && src[j])
		dst[i++] = src[j++];
	if (dstsize > 0 && i > dest_len)
		dst[i] = 0;
	while (src[j])
		j++;
	return (dest_len + j);
}
