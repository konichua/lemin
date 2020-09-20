/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburnett <mburnett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 15:47:18 by mburnett          #+#    #+#             */
/*   Updated: 2019/09/21 10:15:50 by mburnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define SPACES(x) s[x] == ' ' || s[x] == '\n' || s[x] == '\t'
#define SYMBOLS(x) s[x] != ' ' && s[x] != '\n' && s[x] != '\t'

static char	*ft_exist(char const *s, char *p)
{
	size_t len;
	size_t i;

	i = 0;
	len = 0;
	len = ft_strlen(s);
	while (SPACES(len - 1))
	{
		len--;
		if (SYMBOLS(len - 1))
			break ;
	}
	if (len > 0)
	{
		while (SPACES(i))
		{
			i++;
			len--;
			if (SYMBOLS(i))
				break ;
		}
	}
	p = ft_strsub(s, i, len);
	return (p);
}

char		*ft_strtrim(char const *s)
{
	char *p;

	p = NULL;
	if (s && *s)
		p = ft_exist(s, p);
	else
		p = ft_strnew(0);
	if (!p)
		return (NULL);
	return (p);
}
