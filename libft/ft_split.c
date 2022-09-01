/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:39:22 by mfirdous          #+#    #+#             */
/*   Updated: 2022/07/18 12:34:55 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	word_found;
	int	count;

	i = -1;
	count = 0;
	word_found = 0;
	while (s[++i])
	{
		if (s[i] == c && word_found)
		{
			count++;
			word_found = 0;
		}	
		else if (s[i] != c)
			word_found = 1;
	}
	if (word_found)
		count++;
	return (count);
}

static void	ft_init(int *i, int *start, int *wc)
{
	*i = -1;
	*start = -1;
	*wc = 0;
}

static char	**create_list(int *count, const char *s, char c)
{
	char	**list;

	if (!s)
		return (0);
	*count = count_words(s, c);
	list = (char **) malloc((*count + 1) * sizeof(char **));
	if (!list)
		return (0);
	return (list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	int		i;
	int		start;
	int		wc;
	int		count;

	list = create_list(&count, s, c);
	if (!list)
		return (0);
	ft_init(&i, &start, &wc);
	while (wc < count)
	{
		if (s[++i] != c && start == -1)
			start = i;
		else if ((!s[i] || s[i] == c) && (start != -1))
		{
			list[wc] = ft_substr(s, start, i - start);
			if (!list[wc++])
				return (0);
			start = -1;
		}
	}
	list[wc] = 0;
	return (list);
}
