/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strncmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:20:55 by julhong           #+#    #+#             */
/*   Updated: 2025/05/12 17:52:14 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	printf("...starting... Tests:\n\n\n");
	
	char	s1[] = "1234";
	char	s2[] = "1235";
    int     n = 3;
	int     actual = strncmp(s1, s2, n);
	printf("Actual: %d\n", actual);

	int     result = ft_strncmp(s1, s2, n);
	printf("Result: %d\n", result);

	printf("\n\n...end tests...\n");
}