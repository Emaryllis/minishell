/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:20:55 by julhong           #+#    #+#             */
/*   Updated: 2025/05/09 19:05:32 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>
int	main(void)
{
    //regular tests
    printf("...starting... Basic Tests:\n\n\n");
    char *strs[] = {"so long", "and thanks", "for all the fish", NULL};
    int i = 0;
    while (strs[i] != NULL)
    {
        int actual = strlen(strs[i]);
        int result = ft_strlen(strs[i]);
        printf("Input: %s | Actual: %d | Result: %d\n", strs[i], actual, result);
		if (actual != result)
			printf("Wrong\n\n");
        i++;
    }
    printf("\n\n\n");
    
    //edge case: Empty string
    printf("...starting... Edge Tests:\n\n\n");
    char *strs2[] = {"a", " ", "", "0123456789", "abc\0def", "\x01\x02\x03", NULL};
    i = 0;
    while (strs2[i] != NULL)
    {
        int actual = strlen(strs2[i]);
        int result = ft_strlen(strs2[i]);
        printf("Input: %s | Actual: %d | Result: %d\n", strs2[i], actual, result);
		if (actual != result)
			printf("Wrong\n\n");
        i++;
    }
    printf("\n\n\n...end...\n");
}