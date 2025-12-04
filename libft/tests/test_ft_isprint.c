/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_isprint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:20:55 by julhong           #+#    #+#             */
/*   Updated: 2025/05/09 16:25:49 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	int i = -1;
	while (i < 256)
	{
		int result = ft_isprint(i);
		int actual	= isprint(i);

		printf("Input: %d | Actual: %d | Result: %d\n", i, actual, result);
		if (!!actual != !!result)
			printf("Wrong\n\n");
		i++;
	}
}