/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_isascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:52:23 by julhong           #+#    #+#             */
/*   Updated: 2025/05/09 15:16:23 by julhong          ###   ########.fr       */
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
		int result = ft_isascii(i);
		int actual	= isascii(i);

		printf("Input: %d | Actual: %d | Result: %d\n", i, actual, result);
		if (!!actual != !!result)
			printf("Wrong\n\n");
		i++;
	}
}