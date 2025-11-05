/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_isdigit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:01:12 by julhong           #+#    #+#             */
/*   Updated: 2025/05/09 15:16:34 by julhong          ###   ########.fr       */
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
		int result = ft_isdigit(i);
		int actual	= isdigit(i);

		printf("Input: %d | Actual: %d | Result: %d\n", i, actual, result);
		if ((actual != 0 && result != 0) || (actual == 0 && result == 0))
			printf("Correct\n\n");
		else
			printf("Wrong\n\n");
		i++;
	}
}