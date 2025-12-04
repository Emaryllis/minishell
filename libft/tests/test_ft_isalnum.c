/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_isalnum.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:15:15 by julhong           #+#    #+#             */
/*   Updated: 2025/05/09 15:16:14 by julhong          ###   ########.fr       */
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
		int result = ft_isalnum(i);
		int actual	= isalnum(i);

		printf("Input: %d | Actual: %d | Result: %d\n", i, actual, result);
		if (!!actual != !!result)
			printf("Wrong\n\n");
		i++;
	}
}