/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_tolower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:20:55 by julhong           #+#    #+#             */
/*   Updated: 2025/05/09 18:23:03 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
    //regular tests
    printf("...starting... Basic Tests:\n\n\n");
    char cs[] = {'a', 'b', 'c', 'A', 'Z', '\0'};
    int i = 0;
    while (cs[i])
    {
        int actual = tolower(cs[i]);
        int result = ft_tolower(cs[i]);
        printf("Input: %c | Actual: %d | Result: %d\n", cs[i], actual, result);
		if (actual != result)
			printf("Wrong\n\n");
        i++;
    }
    printf("\n\n\n");
    
    //edge case: Empty string
    printf("...starting... Edge Tests:\n\n\n");
    char cs2[] = {'0', '\n', 1, '!', '\0'};
    i = 0;
    while (cs2[i])
    {
        int actual = tolower(cs2[i]);
        int result = ft_tolower(cs2[i]);
        printf("Input: %c | Actual: %d | Result: %d\n", cs2[i], actual, result);
		if (actual != result)
			printf("Wrong\n\n");
        i++;
    }
    printf("\n\n\n...end...\n");
}