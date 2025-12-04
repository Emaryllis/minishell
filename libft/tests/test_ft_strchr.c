/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:20:55 by julhong           #+#    #+#             */
/*   Updated: 2025/05/12 14:28:55 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
    //regular tests
    printf("...starting... Tests:\n\n\n");
    char    *strs[] = {"so long", "and thanks", "for all the fish", NULL};
    char    cs[] = {'s', ' ', '\0'};
    char    *desc[] = {"Single char", "space", "Null terminator"};
    int charsetlen = 3;
    int i = 0;
    while (strs[i] != NULL)
    {
        int j = 0;
        while (j < charsetlen)
        {
            char *actual = strchr(strs[i], cs[j]);
            char *result = ft_strchr(strs[i], cs[j]);
            printf("String: %s | Char: %c | Desc: %s --- Actual: %s | Result: %s\n", strs[i], cs[j], desc[j], actual, result);
            if (actual != result)
                printf("Wrong\n\n");
            j++;
        }
        i++;
    }
    printf("\n\n\n");
}