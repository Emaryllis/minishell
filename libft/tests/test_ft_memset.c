/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_memset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:20:55 by julhong           #+#    #+#             */
/*   Updated: 2025/05/12 14:36:44 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	printf("...starting... Tests:\n\n\n");
	
	char	s1[] = "test";
	char	*actual = memset(s1, '0', 4);
	printf("Actual: %s\n", actual);

	char	s2[] = "test";
	char	*result = ft_memset(s2, '0', 4);
	printf("Result: %s\n", result);

	printf("\n\n...end tests...\n");
}
