/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:27:01 by julhong           #+#    #+#             */
/*   Updated: 2025/05/18 23:50:59 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}

/* static void	iter_toupper(unsigned int i, char * c)
{
	if (i % 2 == 0)
		*c = ft_toupper(*c);
}

#include <stdio.h>
int	main(void)
{
	char s[] = "this is MY string!";
	ft_striteri(s, iter_toupper);
	printf("%s", s);
} */