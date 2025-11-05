/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_isalpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:27:09 by julhong           #+#    #+#             */
/*   Updated: 2025/05/09 15:16:08 by julhong          ###   ########.fr       */
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
		int result = ft_isalpha(i);
		int actual	= isalpha(i);

		printf("Input: %d | Actual: %d | Result: %d\n", i, actual, result);
		if ((actual != 0 && result != 0) || (actual == 0 && result == 0))
			printf("Correct\n\n");
		else
			printf("Wrong\n\n");
		i++;
	}
}